#pragma once

#include "GameObject.h"
namespace Engine
{
	class SceneController : GameObject
	{
	public:
		SceneController(
			const std::string& name,
			const std::shared_ptr<DX::DeviceResources>& deviceResources
			);
		virtual ~SceneController();
		
		void OnWindowResizeEvent();


	private:
	//	virtual void doUpdate(DX::StepTimer const& timer) = 0;
	//	virtual void doRender() = 0;
	//	virtual void doLateRender() = 0;
		virtual void doOnWindowsResizeEvent() = 0;

	private:
		
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;

	};
}

