#include "pch.h"
#include "GameObject.h"
#include "Common/StepTimer.h"
#include "Common/DeviceResources.h"

using namespace Engine;

GameObject::GameObject()
	: m_parent(nullptr)
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

}


void GameObject::SetParent(GameObject* i_newParent)
{
	/* Add me to my new parent children list */
	m_parent = i_newParent;
}

