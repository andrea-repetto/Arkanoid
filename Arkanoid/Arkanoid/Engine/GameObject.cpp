#include "pch.h"
#include "GameObject.h"
#include "Common/StepTimer.h"
#include "Common/DeviceResources.h"

#include <algorithm> 

using namespace Engine;


GameObject::GameObject()
	: m_parent(nullptr)
	, m_localPosition(0, 0, 0)
	, m_localRotationYawPitchRoll(0, 0, 0)
	, m_localScale(1, 1, 1)
	, m_Enable(true)

{
}


GameObject::~GameObject()
{
}



/************************************************************************/
/* PUBLIC                                                               */
/************************************************************************/

void GameObject::Start()
{
	doStart();

}

void GameObject::Render()
{
	if (!IsEnable()) return; 

	/* Update my render */
	doRender();
}

void GameObject::Update(DX::StepTimer const& timer)
{
	if (!IsEnable()) return;

	/* Update myself */
	doUpdate(timer);
}


void GameObject::SetParent(GameObject* i_newParent)
{
	/* Add me to my new parent children list */
	m_parent = i_newParent;
}


DirectX::XMFLOAT3 GameObject::GetGlobalPosition() const
{
	DirectX::XMFLOAT3 globalPosition(0, 0, 0);
	if (m_parent)
	{
		globalPosition = m_parent->GetGlobalPosition();
	}

	globalPosition.x = globalPosition.x + m_localPosition.x;
	globalPosition.y = globalPosition.y + m_localPosition.y;
	globalPosition.z = globalPosition.z + m_localPosition.z;

	return globalPosition;
}

DirectX::XMFLOAT3 GameObject::GetGlobalScale() const
{
	DirectX::XMFLOAT3 globalScale(1, 1, 1);
	if (m_parent)
	{
		globalScale = m_parent->GetGlobalScale();
	}

	globalScale.x = globalScale.x * m_localScale.x;
	globalScale.y = globalScale.y * m_localScale.y;
	globalScale.z = globalScale.z * m_localScale.z;

	return globalScale;
}

DirectX::XMFLOAT3 GameObject::GetGlobalRotationYawPitchRoll() const
{
	DirectX::XMFLOAT3 globalRotation(0, 0, 0);
	if (m_parent)
	{
		globalRotation = m_parent->GetGlobalRotationYawPitchRoll();
	}

	globalRotation.x = globalRotation.x + m_localRotationYawPitchRoll.x;
	globalRotation.y = globalRotation.y + m_localRotationYawPitchRoll.y;
	globalRotation.z = globalRotation.z + m_localRotationYawPitchRoll.z;

	return globalRotation;
}

void GameObject::RegisterForEvents(GameObject* obj)
{
	std::vector<GameObject*>::iterator it = std::find(m_Observers.begin(), m_Observers.end(), obj);

	if (it == m_Observers.end())
	{
		m_Observers.push_back(obj);
	}
}

void GameObject::UnregisterFromEvents(GameObject* obj)
{
	std::vector<GameObject*>::iterator it = std::find(m_Observers.begin(), m_Observers.end(), obj);

	if (it != m_Observers.end())
	{
		m_Observers.erase(it);
	}
}

/**
*	Data is optional.
*/
void GameObject::NotifyEvent(int event, GameObject* data)
{
	for (size_t idx = 0; idx < m_Observers.size(); ++idx)
	{
		m_Observers[idx]->OnEvent(this, event, data);
	}
}

void GameObject::OnEvent(GameObject* src, int event, GameObject* data)
{

}






