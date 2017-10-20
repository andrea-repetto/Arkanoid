#pragma once



namespace Engine
{
	struct ViewProjectionMatrix
	{
		DirectX::XMFLOAT4X4		view;
		DirectX::XMFLOAT4X4		projection;
	};

	class Camera
	{
	public:
		explicit Camera();
		~Camera();

		DirectX::XMFLOAT4X4 GetViewMatrix() const { return m_viewProjMatrix.view; }
		DirectX::XMFLOAT4X4 GetProjMatrix() const { return m_viewProjMatrix.projection; }
		D3D12_RECT			GetScissorRect() const { return m_scissorRect; }

		void CreateWindowSizeDependentResources();

	private:
		//static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;
		ViewProjectionMatrix	m_viewProjMatrix;
		D3D12_RECT				m_scissorRect;
		
	};
}

