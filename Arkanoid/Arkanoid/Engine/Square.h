#pragma once

#include "Content/ShaderStructures.h"
/** Forward Declarations */
namespace DX
{
	class StepTimer;
}

namespace Engine
{

	class Square
	{
	public:
		Square();
		~Square();

		void Update(DX::StepTimer const& timer);
		bool Render();

	private:
		static const UINT c_alignedConstantBufferSize = (sizeof(Arkanoid::ModelViewProjectionConstantBuffer) + 255) & ~255;

		Arkanoid::ModelViewProjectionConstantBuffer					m_constantBufferData;


		bool m_loadingComplete;

		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_cbvHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_constantBuffer;

		std::vector<byte>									m_vertexShader;
		std::vector<byte>									m_pixelShader;

		UINT												m_cbvDescriptorSize;

		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;

		UINT8*												m_mappedConstantBuffer;

		D3D12_RECT											m_scissorRect;



		float	m_radiansPerSecond;
		float	m_angle;
	};

}

