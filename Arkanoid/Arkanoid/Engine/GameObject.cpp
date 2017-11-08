#include "pch.h"
#include "GameObject.h"
#include "Common/StepTimer.h"
#include "Common/DeviceResources.h"

using namespace Engine;


GameObject::GameObject()
	: m_parent(nullptr)
	, m_localPosition(0, 0, 0)
	, m_localRotationYawPitchRoll(0, 0, 0)
	, m_localScale(1, 1, 1)

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
	/* Update my render */
	doRender();
}

void GameObject::Update(DX::StepTimer const& timer)
{
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






