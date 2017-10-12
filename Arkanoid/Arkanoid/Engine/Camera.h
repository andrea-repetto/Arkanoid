#pragma once
namespace Engine
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void CreateWindowSizeDependentResources();

	private:
		DirectX::XMFLOAT4X4 m_ViewMatrix;
		DirectX::XMFLOAT4X4 m_ProjectionMatrix;
		D3D12_RECT			m_scissorRect;
	};
}

