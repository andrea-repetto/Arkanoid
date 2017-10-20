#pragma once

#include "GameObject.h"

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
};

namespace Engine
{

	class Square: public GameObject
	{
	public:
		Square();
		~Square();

	private:
		void doStart() override;
		void doUpdate(DX::StepTimer const& timer) override;
		bool doRender() override;
		bool doLateRender() override;

	private:
		// Constant buffers must be 256-byte aligned.
		static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;

		ModelViewProjectionConstantBuffer					m_constantBufferData;

		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_constantBuffer;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_cbvHeap;

		UINT8*												m_mappedConstantBuffer;
		UINT												m_cbvDescriptorSize;

		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;



		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_radiansPerSecond;
		float	m_angle;
		bool	m_tracking;

		Microsoft::WRL::ComPtr<ID3DBlob>									m_vertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob>									m_pixelShader;
		//std::vector<byte>									m_vertexShader;
		//std::vector<byte>									m_pixelShader;
	};

}

