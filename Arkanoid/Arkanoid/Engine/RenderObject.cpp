#include "pch.h"
#include "RenderObject.h"
#include "Camera.h"
#include "GameEngine.h"

#include "Common\d3dUtil.h"
#include "Common\StepTimer.h"

#include "Camera.h"

using namespace Engine;
using namespace DirectX;

RenderObject::RenderObject(
	const Vertex* 										vertexList,
	UINT												vertexListSize,
	const unsigned short* 								indexList,
	UINT												indexListSize)
	: GameObject()
	, m_vertexShaderFileName(L"SampleVertexShader.cso")
	, m_pixelShaderFileName(L"SamplePixelShader.cso")
	, m_vertexList(vertexList)
	, m_vertexListSize(vertexListSize)
	, m_indexList(indexList)
	, m_indexListSize(indexListSize)
{
	assert(m_vertexList != nullptr && m_indexList != nullptr && "Vertex List and Index List cannot be Null in Render Object!");
	ZeroMemory(&m_constantBufferData, sizeof(m_constantBufferData));

	//Set matirial to red color by default
	m_constantBufferData.material.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	
}


RenderObject::~RenderObject()
{
}


void RenderObject::doStart()
{
	auto d3dDevice = GameEngine::Instance()->DeviceResources()->GetD3DDevice();

	DX::ThrowIfFailed(GameEngine::Instance()->DeviceResources()->GetCommandAllocator()->Reset());

	// The command list can be reset anytime after ExecuteCommandList() is called.
	DX::ThrowIfFailed(GameEngine::Instance()->CommandList()->Reset(GameEngine::Instance()->DeviceResources()->GetCommandAllocator(), nullptr));

	//ID3DBlob* PS_Buffer;

	D3DReadFileToBlob(m_vertexShaderFileName, &m_vertexShader);
	D3DReadFileToBlob(m_pixelShaderFileName, &m_pixelShader);


	// Create the pipeline state once the shaders are loaded.
	//auto createPipelineStateTask = (createPSTask && createVSTask).then([this]() {

	static const D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC state = {};
	state.InputLayout = { inputLayout, _countof(inputLayout) };
	state.pRootSignature = GameEngine::Instance()->RootSignature().Get();
	state.VS =
	{
		reinterpret_cast<BYTE*>(m_vertexShader->GetBufferPointer()),
		m_vertexShader->GetBufferSize()
	};
	//CD3DX12_SHADER_BYTECODE(&m_vertexShader[0], m_vertexShader.size());
	state.PS = {
		reinterpret_cast<BYTE*>(m_pixelShader->GetBufferPointer()),
		m_pixelShader->GetBufferSize()
	};//CD3DX12_SHADER_BYTECODE(&m_pixelShader[0], m_pixelShader.size());
	state.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	state.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	state.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	state.SampleMask = UINT_MAX;
	state.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	state.NumRenderTargets = 1;
	state.RTVFormats[0] = GameEngine::Instance()->DeviceResources()->GetBackBufferFormat();
	state.DSVFormat = GameEngine::Instance()->DeviceResources()->GetDepthBufferFormat();
	state.SampleDesc.Count = 1;

	DX::ThrowIfFailed(GameEngine::Instance()->DeviceResources()->GetD3DDevice()->CreateGraphicsPipelineState(&state, IID_PPV_ARGS(&m_pipelineState)));


	GameEngine::Instance()->CommandList()->SetPipelineState(m_pipelineState.Get());

	const UINT vertexBufferSize = sizeof(Vertex)*m_vertexListSize;

	// Create the vertex buffer resource in the GPU's default heap and copy vertex data into it using the upload heap.
	// The upload resource must not be released until after the GPU has finished using it.
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBufferUpload;

	CD3DX12_HEAP_PROPERTIES defaultHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC vertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
	DX::ThrowIfFailed(d3dDevice->CreateCommittedResource(
		&defaultHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexBufferDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_vertexBuffer)));

	CD3DX12_HEAP_PROPERTIES uploadHeapProperties(D3D12_HEAP_TYPE_UPLOAD);
	DX::ThrowIfFailed(d3dDevice->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexBufferUpload)));

	NAME_D3D12_OBJECT(m_vertexBuffer);

	// Upload the vertex buffer to the GPU.
	{
		D3D12_SUBRESOURCE_DATA vertexData = {};
		vertexData.pData = reinterpret_cast<const BYTE*>(m_vertexList);
		vertexData.RowPitch = vertexBufferSize;
		vertexData.SlicePitch = vertexData.RowPitch;

		UpdateSubresources(GameEngine::Instance()->CommandList().Get(), m_vertexBuffer.Get(), vertexBufferUpload.Get(), 0, 0, 1, &vertexData);

		CD3DX12_RESOURCE_BARRIER vertexBufferResourceBarrier =
			CD3DX12_RESOURCE_BARRIER::Transition(m_vertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
		GameEngine::Instance()->CommandList()->ResourceBarrier(1, &vertexBufferResourceBarrier);
	}

	// Load mesh indices. Each trio of indices represents a triangle to be rendered on the screen.
	// For example: 0,2,1 means that the vertices with indexes 0, 2 and 1 from the vertex buffer compose the
	// first triangle of this mesh.

	const UINT indexBufferSize = m_indexListSize * sizeof(unsigned short); //sizeof(cubeIndices);

	// Create the index buffer resource in the GPU's default heap and copy index data into it using the upload heap.
	// The upload resource must not be released until after the GPU has finished using it.
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBufferUpload;

	CD3DX12_RESOURCE_DESC indexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);
	DX::ThrowIfFailed(d3dDevice->CreateCommittedResource(
		&defaultHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&indexBufferDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_indexBuffer)));

	DX::ThrowIfFailed(d3dDevice->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&indexBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBufferUpload)));

	NAME_D3D12_OBJECT(m_indexBuffer);

	// Upload the index buffer to the GPU.
	{
		D3D12_SUBRESOURCE_DATA indexData = {};
		indexData.pData = reinterpret_cast<const BYTE*>(m_indexList);
		indexData.RowPitch = indexBufferSize;
		indexData.SlicePitch = indexData.RowPitch;

		UpdateSubresources(GameEngine::Instance()->CommandList().Get(), m_indexBuffer.Get(), indexBufferUpload.Get(), 0, 0, 1, &indexData);

		CD3DX12_RESOURCE_BARRIER indexBufferResourceBarrier =
			CD3DX12_RESOURCE_BARRIER::Transition(m_indexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER);
		GameEngine::Instance()->CommandList()->ResourceBarrier(1, &indexBufferResourceBarrier);
	}

	// Create a descriptor heap for the constant buffers.
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.NumDescriptors = DX::c_frameCount;
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		// This flag indicates that this descriptor heap can be bound to the pipeline and that descriptors contained in it can be referenced by a root table.
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		DX::ThrowIfFailed(d3dDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_cbvHeap)));

		NAME_D3D12_OBJECT(m_cbvHeap);
	}

	CD3DX12_RESOURCE_DESC constantBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(DX::c_frameCount * c_alignedConstantBufferSize);
	DX::ThrowIfFailed(d3dDevice->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&constantBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_constantBuffer)));

	NAME_D3D12_OBJECT(m_constantBuffer);

	// Create constant buffer views to access the upload buffer.
	D3D12_GPU_VIRTUAL_ADDRESS cbvGpuAddress = m_constantBuffer->GetGPUVirtualAddress();
	CD3DX12_CPU_DESCRIPTOR_HANDLE cbvCpuHandle(m_cbvHeap->GetCPUDescriptorHandleForHeapStart());
	m_cbvDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	for (int n = 0; n < DX::c_frameCount; n++)
	{
		D3D12_CONSTANT_BUFFER_VIEW_DESC desc;
		desc.BufferLocation = cbvGpuAddress;
		desc.SizeInBytes = c_alignedConstantBufferSize;
		d3dDevice->CreateConstantBufferView(&desc, cbvCpuHandle);

		cbvGpuAddress += desc.SizeInBytes;
		cbvCpuHandle.Offset(m_cbvDescriptorSize);
	}

	// Map the constant buffers.
	CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
	DX::ThrowIfFailed(m_constantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_mappedConstantBuffer)));
	// We don't unmap this until the app closes. Keeping things mapped for the lifetime of the resource is okay.

	// Close the command list and execute it to begin the vertex/index buffer copy into the GPU's default heap.
	DX::ThrowIfFailed(GameEngine::Instance()->CommandList()->Close());
	ID3D12CommandList* ppCommandLists[] = { GameEngine::Instance()->CommandList().Get() };
	GameEngine::Instance()->DeviceResources()->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// Create vertex/index buffer views.
	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.StrideInBytes = sizeof(Vertex);
	m_vertexBufferView.SizeInBytes = vertexBufferSize;

	m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
	m_indexBufferView.SizeInBytes = indexBufferSize;
	m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;

	// Wait for the command list to finish executing; the vertex/index buffers need to be uploaded to the GPU before the upload resources go out of scope.
	GameEngine::Instance()->DeviceResources()->WaitForGpu();

	m_vertexList = nullptr;
	m_indexList = nullptr;
}

void RenderObject::doUpdate(DX::StepTimer const& timer)
{
	/* Update matrix transformation */
	std::shared_ptr<Camera> currentActiveCamera = GameEngine::Instance()->GetActiveCamera();
	std::shared_ptr<DirectionalLight> dirLight = GameEngine::Instance()->GetDirectionalLight();
	std::shared_ptr<AmbientLight> ambientLight = GameEngine::Instance()->GetAmbientLight();
	m_constantBufferData.projection = currentActiveCamera->GetProjMatrix();
	m_constantBufferData.view = currentActiveCamera->GetViewMatrix();
	m_constantBufferData.ambientLight = *ambientLight;
	m_constantBufferData.dirLight = *dirLight;
	
	XMFLOAT3 globalScale = this->GetGlobalScale();
	XMFLOAT3 globalRotation = this->GetGlobalRotationYawPitchRoll();
	XMFLOAT3 globalTransform = this->GetGlobalTransform();
	

	XMMATRIX scaling = XMMatrixScaling(globalScale.x, globalScale.y, globalScale.z);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(globalRotation.y, globalRotation.z, globalRotation.x);
	XMMATRIX transform = XMMatrixTranslation(globalTransform.x, globalTransform.y, globalTransform.z);

	XMMATRIX scalRot = XMMatrixMultiply(scaling, rotation);
	XMMATRIX transf = XMMatrixMultiply(scalRot, transform);

	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(transf));

	UINT8* destination = m_mappedConstantBuffer + (GameEngine::Instance()->DeviceResources()->GetCurrentFrameIndex() * c_alignedConstantBufferSize);
	memcpy(destination, &m_constantBufferData, sizeof(m_constantBufferData));
}

void RenderObject::doRender()
{
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = GameEngine::Instance()->CommandList();
	std::shared_ptr<DX::DeviceResources> deviceResources = GameEngine::Instance()->DeviceResources();
	Microsoft::WRL::ComPtr<ID3D12RootSignature>	rootSignature = GameEngine::Instance()->RootSignature();


	PIXBeginEvent(commandList.Get(), 0, L"Draw the cube");
	{

		ID3D12DescriptorHeap* ppHeaps[] = { m_cbvHeap.Get() };
		commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

		// Bind the current frame's constant buffer to the pipeline.
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(m_cbvHeap->GetGPUDescriptorHandleForHeapStart(), deviceResources->GetCurrentFrameIndex(), m_cbvDescriptorSize);
		commandList->SetGraphicsRootDescriptorTable(0, gpuHandle);


		commandList->SetPipelineState(m_pipelineState.Get());
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
		commandList->IASetIndexBuffer(&m_indexBufferView);
		commandList->DrawIndexedInstanced(m_indexListSize, 1, 0, 0, 0);



	}
	PIXEndEvent(commandList.Get());
}

void RenderObject::SetMeshData(
	const Vertex*				vertexList,
	UINT						vertexListSize,
	const unsigned short*		indexList,
	UINT						indexListSize
)
{
	m_vertexList = vertexList;
	m_indexList = indexList;
	m_vertexListSize = vertexListSize;
	m_indexListSize = indexListSize;

	assert(m_vertexList != nullptr && m_indexList != nullptr && "Vertex List and Index List cannot be Null in Render Object!");
}


/**
void RenderObject::computeVertexNormals()
{
	UINT triangleNumber = m_indexListSize / 3;
	for (UINT idx = 0; idx < triangleNumber; ++idx)
	{
		UINT i0 = m_indexList[idx * 3 + 0];
		UINT i1 = m_indexList[idx * 3 + 1];
		UINT i2 = m_indexList[idx * 3 + 2];

		Vertex v0 = m_vertexList[i0];
		Vertex v1 = m_vertexList[i1];
		Vertex v2 = m_vertexList[i2];

		XMVECTOR v0Pos = XMLoadFloat3(&v0.pos);
		XMVECTOR v1Pos = XMLoadFloat3(&v1.pos);
		XMVECTOR v2Pos = XMLoadFloat3(&v2.pos);

		XMVECTOR e0 = v1Pos - v0Pos;
		XMVECTOR e1 = v2Pos - v0Pos;

		XMVECTOR faceNormal = XMVector3Cross(e0, e1);
		XMFLOAT3 faceNormalFloat3;

		XMStoreFloat3(&faceNormalFloat3, faceNormal);

		
		m_vertexList[i0].normal.x += faceNormalFloat3.x;
		m_vertexList[i0].normal.y += faceNormalFloat3.y;
		m_vertexList[i0].normal.z += faceNormalFloat3.z;

		m_vertexList[i1].normal.x += faceNormalFloat3.x;
		m_vertexList[i1].normal.y += faceNormalFloat3.y;
		m_vertexList[i1].normal.z += faceNormalFloat3.z;

		m_vertexList[i2].normal.x += faceNormalFloat3.x;
		m_vertexList[i2].normal.y += faceNormalFloat3.y;
		m_vertexList[i2].normal.z += faceNormalFloat3.z;
	
	}

	
	for (UINT idx = 0; idx < m_vertexListSize; ++idx)
	{
		XMVECTOR normal = XMLoadFloat3(&(m_vertexList[idx].normal));
		normal = XMVector3Normalize(normal);

		XMStoreFloat3(&(m_vertexList[idx].normal), normal);

	}


}
*/