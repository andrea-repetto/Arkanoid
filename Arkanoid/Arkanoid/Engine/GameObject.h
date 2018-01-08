#pragma once

#include <vector>
#include <string>
#include <DirectXMath.h>

/** Forward Declarations */
namespace DX
{
	class StepTimer;
}

namespace Engine
{
	class GameObject
	{
	public:
		explicit GameObject( );
		virtual ~GameObject();

		void Start();
		void Render();
		void Update(DX::StepTimer const& timer);
		void SetParent(GameObject* i_newParent);
		inline const GameObject* GetParent() const { return m_parent; }


		inline DirectX::XMFLOAT3 GetLocalPosition() const { return m_localPosition; }
		inline DirectX::XMFLOAT3 GetLocalScale() const { return m_localScale; }
		inline DirectX::XMFLOAT3 GetLocalRotationYawPitchRoll() const { return m_localRotationYawPitchRoll; }

		DirectX::XMFLOAT3 GetGlobalPosition() const ;
		DirectX::XMFLOAT3 GetGlobalScale() const;
		DirectX::XMFLOAT3 GetGlobalRotationYawPitchRoll() const;
		
		inline void SetLocalPosition(const DirectX::XMFLOAT3& position) { m_localPosition = position; }
		inline void SetLocalScale(const DirectX::XMFLOAT3& scale) { m_localScale = scale; }
		inline void SetLocalRotationYawPitchRoll(const DirectX::XMFLOAT3& rotationYawPitchRoll) { m_localRotationYawPitchRoll = rotationYawPitchRoll; }

		inline bool IsEnable() const { return m_Enable; }
		inline void SetEnable(bool val) { m_Enable = val; }


		void RegisterForEvents( GameObject* obj);
		void UnregisterFromEvents( GameObject* obj);

	protected:
		virtual void doStart() = 0;
		virtual void doUpdate(DX::StepTimer const& timer) = 0;
		virtual void doRender() = 0;

		virtual void OnEvent(GameObject* src, int event, GameObject* data);
		
	private:
		void NotifyEvent(int event, GameObject* data);

	private:
		
		DirectX::XMFLOAT3		m_localPosition;
		DirectX::XMFLOAT3		m_localRotationYawPitchRoll;
		DirectX::XMFLOAT3		m_localScale;

	protected:
		GameObject*				m_parent;
		std::vector<GameObject*> m_Observers;
		bool					m_Enable;
	};
}

