#pragma once
/************************************************************************/
/* This class give access to global resources                           */
/************************************************************************/


namespace DX
{
	class DeviceResources;
}

namespace Engine
{
	class GameEngine
	{

	public:
		static GameEngine* Instance();

		void Initialize(const std::shared_ptr<DX::DeviceResources>& deviceResources );

		std::shared_ptr<DX::DeviceResources> DeviceResources() const { return m_deviceResources; }
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList() const { return m_commandList;  }
		Microsoft::WRL::ComPtr<ID3D12RootSignature> RootSignature() const { return m_rootSignature;  }


	private:
		GameEngine();
		~GameEngine();

		GameEngine(const GameEngine&);
		GameEngine& operator=(const GameEngine&) = default;


	private:
		static GameEngine* s_Instance;

		std::shared_ptr<DX::DeviceResources>				m_deviceResources;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
	};
}

