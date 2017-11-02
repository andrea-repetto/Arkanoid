#include "pch.h"
#include "GameEngine.h"
#include "Camera.h"
#include "Light.h"


using namespace Engine;
using namespace Microsoft::WRL;

GameEngine* GameEngine::s_Instance = nullptr;

GameEngine::GameEngine()
	: m_deviceResources(nullptr)
	, m_rootSignature(nullptr)
	, m_commandList(nullptr)
{
}


GameEngine::~GameEngine()
{
}



GameEngine* GameEngine::Instance()
{
	if (!s_Instance)
	{
		s_Instance = new GameEngine();
	}

	return s_Instance;
}


void GameEngine::Initialize(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	m_deviceResources = deviceResources;

	/* Init default camera */
	m_activeCamera = std::make_shared<Camera>();

	/* Init default lights  (Only one directional light and one ambient light */
	m_directionalLight = std::make_shared<DirectionalLight>();
	m_ambientLight = std::make_shared<AmbientLight>();

	m_directionalLight->Strenght = { 0.6f, 0.6f, 0.6f, 1.0f };
	m_directionalLight->Direction = { 0.57735f, -0.57735f, 0.57735f, 0.0f };

	m_ambientLight->Strenght = { 0.25f, 0.25f, 0.35f, 1.0f };

	/* init GPU global data */
	auto d3dDevice = m_deviceResources->GetD3DDevice();

	// Create a root signature with a single constant buffer slot.
	{
		CD3DX12_DESCRIPTOR_RANGE range;
		CD3DX12_ROOT_PARAMETER parameter;

		range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
		parameter.InitAsDescriptorTable(1, &range, D3D12_SHADER_VISIBILITY_ALL);

		D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | // Only the input assembler stage needs access to the constant buffer.
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS; // |
			//D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

		CD3DX12_ROOT_SIGNATURE_DESC descRootSignature;
		descRootSignature.Init(1, &parameter, 0, nullptr, rootSignatureFlags);

		ComPtr<ID3DBlob> pSignature;
		ComPtr<ID3DBlob> pError;
		DX::ThrowIfFailed(D3D12SerializeRootSignature(&descRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, pSignature.GetAddressOf(), pError.GetAddressOf()));
		DX::ThrowIfFailed(d3dDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));
		NAME_D3D12_OBJECT(m_rootSignature);
	}

	/* Create command list */
	// Create a command list.
	DX::ThrowIfFailed(d3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_deviceResources->GetCommandAllocator(), nullptr, IID_PPV_ARGS(&m_commandList)));
	NAME_D3D12_OBJECT(m_commandList);

	// Close the command list and execute it to begin the vertex/index buffer copy into the GPU's default heap.
	DX::ThrowIfFailed(m_commandList->Close());
	ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
	m_deviceResources->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	m_deviceResources->WaitForGpu();
}



void GameEngine::BeginScene()
{
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = GameEngine::Instance()->CommandList();
	std::shared_ptr<DX::DeviceResources> deviceResources = GameEngine::Instance()->DeviceResources();
	Microsoft::WRL::ComPtr<ID3D12RootSignature>	rootSignature = GameEngine::Instance()->RootSignature();
	std::shared_ptr<Camera> currentCamera = GameEngine::Instance()->GetActiveCamera();

	DX::ThrowIfFailed(deviceResources->GetCommandAllocator()->Reset());

	// The command list can be reset anytime after ExecuteCommandList() is called.
	DX::ThrowIfFailed(commandList->Reset(deviceResources->GetCommandAllocator(), nullptr));

	// Set the graphics root signature and descriptor heaps to be used by this frame.
	commandList->SetGraphicsRootSignature(rootSignature.Get());

	// Indicate this resource will be in use as a render target.
	CD3DX12_RESOURCE_BARRIER renderTargetResourceBarrier =
		CD3DX12_RESOURCE_BARRIER::Transition(deviceResources->GetRenderTarget(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	commandList->ResourceBarrier(1, &renderTargetResourceBarrier);

	// Record drawing commands.
	D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView = deviceResources->GetRenderTargetView();
	D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView = deviceResources->GetDepthStencilView();
	commandList->ClearRenderTargetView(renderTargetView, DirectX::Colors::CornflowerBlue, 0, nullptr);
	commandList->ClearDepthStencilView(depthStencilView, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	commandList->OMSetRenderTargets(1, &renderTargetView, false, &depthStencilView);

	// Set the viewport and scissor rectangle.
	D3D12_VIEWPORT viewport = deviceResources->GetScreenViewport();
	commandList->RSSetViewports(1, &viewport);
	commandList->RSSetScissorRects(1, &(currentCamera->GetScissorRect()));

}

void GameEngine::EndScene()
{
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = GameEngine::Instance()->CommandList();
	std::shared_ptr<DX::DeviceResources> deviceResources = GameEngine::Instance()->DeviceResources();
	Microsoft::WRL::ComPtr<ID3D12RootSignature>	rootSignature = GameEngine::Instance()->RootSignature();

	// Indicate that the render target will now be used to present when the command list is done executing.
	CD3DX12_RESOURCE_BARRIER presentResourceBarrier =
		CD3DX12_RESOURCE_BARRIER::Transition(deviceResources->GetRenderTarget(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	commandList->ResourceBarrier(1, &presentResourceBarrier);

	DX::ThrowIfFailed(commandList->Close());

	// Execute the command list.
	ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
	deviceResources->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

