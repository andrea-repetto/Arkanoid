#pragma once
#include "GameObject.h"
#include "Light.h"
#include "Common\GeometryGenerator.h"

namespace Engine
{
	struct Material
	{
		DirectX::XMFLOAT4 color;
	};
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
		DirectionalLight	dirLight;
		AmbientLight		ambientLight;
		Material			material;

	};

	// Used to send per-vertex data to the vertex shader.
	using Vertex = GeometryGenerator::Vertex;

	class RenderObject: public GameObject
	{
	public:
		explicit RenderObject(
			const Vertex* 										vertexList,
			UINT												vertexListSize,
			const std::uint32_t* 									indexList,
			UINT												indexListSize);
		virtual ~RenderObject();

		inline LPCWSTR GetVertexShaderFileName() const { return m_vertexShaderFileName; }
		inline LPCWSTR GetPixelShaderFileName() const { return m_pixelShaderFileName; }
		inline void SetVertexShaderFileName(const LPCWSTR& vertexShaderFileName) { m_vertexShaderFileName = vertexShaderFileName; }
		inline void SetPixelShaderFileName(const LPCWSTR& pixelShaderFileName) { m_pixelShaderFileName = pixelShaderFileName; }

		inline Material GetMaterial() const { return m_constantBufferData.material; }
		inline void SetMaterial(const Material& material) { m_constantBufferData.material = material; }


		void SetMeshData(
			const Vertex* vertexList,
			UINT						vertexListSize,
			const std::uint32_t*				indexList,
			UINT						    indexListSize			
		);

	private:
		void doStart() override;
		void doUpdate(DX::StepTimer const& timer) override;
		void doRender() override;

		//void computeVertexNormals();

	private:
		LPCWSTR												m_vertexShaderFileName;
		LPCWSTR												m_pixelShaderFileName;
		const Vertex* 										m_vertexList;
		UINT												m_vertexListSize;
		const std::uint32_t* 								m_indexList;
		UINT												m_indexListSize;

		UINT8*												m_mappedConstantBuffer;
		static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;

		ModelViewProjectionConstantBuffer					m_constantBufferData;


		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_constantBuffer;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_cbvHeap;


		UINT												m_cbvDescriptorSize;

		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;

		Microsoft::WRL::ComPtr<ID3DBlob>					m_vertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob>					m_pixelShader;

	};
}

