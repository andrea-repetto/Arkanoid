#pragma once
#include "GameObject.h"
#include "Light.h"
#include "Common\GeometryGenerator.h"
#include "GameEngine.h"

namespace Engine
{
	struct Material
	{
		DirectX::XMFLOAT4 color;

		Material(float x, float y, float z, float w)
		{
			color.x = x;
			color.y = y;
			color.z = z;
			color.w = w;
		}
		Material(float x, float y, float z) : Material(x, y, z, 1.0f) {}
		Material() : Material(1.0f, 0.0f, 0.0f) {}

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


	class RenderObject: public GameObject
	{
	public:
		explicit RenderObject(const MeshData &mesh);
		explicit RenderObject(int ID, const MeshData &mesh);
		virtual ~RenderObject();

		inline LPCWSTR GetVertexShaderFileName() const { return m_vertexShaderFileName; }
		inline LPCWSTR GetPixelShaderFileName() const { return m_pixelShaderFileName; }
		inline void SetVertexShaderFileName(const LPCWSTR& vertexShaderFileName) { m_vertexShaderFileName = vertexShaderFileName; }
		inline void SetPixelShaderFileName(const LPCWSTR& pixelShaderFileName) { m_pixelShaderFileName = pixelShaderFileName; }

		inline Material GetMaterial() const { return m_constantBufferData.material; }
		inline void SetMaterial(const Material& material) { m_constantBufferData.material = material; }

	private:
		void doStart() override;
		void doUpdate(DX::StepTimer const& timer) override;
		void doRender() override;

		//void computeVertexNormals();

	private:
		LPCWSTR												m_vertexShaderFileName;
		LPCWSTR												m_pixelShaderFileName;

		const MeshData									  &m_Mesh;

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

