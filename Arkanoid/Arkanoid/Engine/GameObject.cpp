#include "pch.h"
#include "GameObject.h"
#include "Common/StepTimer.h"
#include "Common/DeviceResources.h"

using namespace Engine;

GameObject::GameObject()
	: m_parent(nullptr)
	, m_localTransform(0, 0, 0)
	, m_globalTransform(0, 0, 0)
	, m_localRotationYawPitchRoll(0, 0, 0)
	, m_globalRotationYawPitchRoll(0, 0, 0)
	, m_localScale(1, 1, 1)
	, m_globalScale(1, 1, 1)
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

bool GameObject::Render()
{
	/* Update my render */
	if (!doRender()) return false;

	return true;
}

void GameObject::Update(DX::StepTimer const& timer)
{
	/* Update myself */
	doUpdate(timer);

	/* Update matrix transformation */

}


void GameObject::SetParent(GameObject* i_newParent)
{
	/* Add me to my new parent children list */
	m_parent = i_newParent;
}


void GameObject::SetLocalTransform(DirectX::XMFLOAT3& transform)
{
	m_localTransform = transform;
	DirectX::XMFLOAT3 parentGlobalTransform(0, 0, 0);
	if (m_parent)
	{
		parentGlobalTransform = m_parent->GetGlobalTransform();
	}

	m_globalTransform.x = parentGlobalTransform.x + transform.x;
	m_globalTransform.y = parentGlobalTransform.y + transform.y;
	m_globalTransform.z = parentGlobalTransform.z + transform.z;
}

void GameObject::SetLocalScale(DirectX::XMFLOAT3& scale)
{
	m_localScale = scale;
	DirectX::XMFLOAT3 parentGlobalScale(1, 1, 1);
	if (m_parent)
	{
		parentGlobalScale = m_parent->GetGlobalScale();
	}

	m_globalScale.x = parentGlobalScale.x * m_localScale.x;
	m_globalScale.y = parentGlobalScale.y * m_localScale.y;
	m_globalScale.z = parentGlobalScale.z * m_localScale.z;
}

void GameObject::SetLocalRotationYawPitchRoll(DirectX::XMFLOAT3& rotationYawPitchRoll)
{
	m_localRotationYawPitchRoll = rotationYawPitchRoll;
	DirectX::XMFLOAT3 parentRotation(0, 0, 0);
	if (m_parent)
	{
		parentRotation = m_parent->GetGlobalRotationYawPitchRoll();
	}

	m_globalRotationYawPitchRoll.x = parentRotation.x + m_localRotationYawPitchRoll.x;
	m_globalRotationYawPitchRoll.y = parentRotation.y + m_localRotationYawPitchRoll.y;
	m_globalRotationYawPitchRoll.z = parentRotation.z + m_localRotationYawPitchRoll.z;
}






