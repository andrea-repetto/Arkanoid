#pragma once
#include "GameObject.h"
namespace Engine
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
		DirectX::XMFLOAT3 normal;
	};

	class RenderObject: public GameObject
	{
	public:
		explicit RenderObject();
		virtual ~RenderObject();

		inline LPCWSTR GetVertexShaderFileName() const { return m_vertexShaderFileName; }
		inline LPCWSTR GetPixelShaderFileName() const { return m_pixelShaderFileName; }
		inline void SetVertexShaderFileName(const LPCWSTR& vertexShaderFileName) { m_vertexShaderFileName = vertexShaderFileName; }
		inline void SetPixelShaderFileName(const LPCWSTR& pixelShaderFileName) { m_pixelShaderFileName = pixelShaderFileName; }

		void SetObjectByVertex(
			const VertexPositionColor*	vertexList, 
			const UINT					vertexListSize,
			const unsigned short*		indexList,
			const UINT					indexListSize
			);

	private:
		void doStart() override;
		void doUpdate(DX::StepTimer const& timer) override;
		void doRender() override;

		void computeVertexNormals();

	private:
		LPCWSTR												m_vertexShaderFileName;
		LPCWSTR												m_pixelShaderFileName;
		VertexPositionColor*								m_vertexList;
		UINT												m_vertexListSize;
		unsigned short*										m_indexList;
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

