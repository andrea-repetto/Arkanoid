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

	std::vector<GameObject*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->Start();
	}
}

void GameObject::Render()
{
	/* Update my render */
	doRender();

	/* Update my children render*/
	std::vector<GameObject*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->Render();
	}

	doLateRender();
}

void GameObject::Update(DX::StepTimer const& timer)
{
	/* Update myself */
	doUpdate(timer);

	/* Update my children */
	std::vector<GameObject*>::iterator it;
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->Update(timer);
	}
}


void GameObject::SetParent(GameObject* i_newParent)
{
	/* Remove from my current parent*/
	if (m_parent)
	{
		m_parent->removeChild(this);
		m_parent = nullptr;
	}

	/* Add me to my new parent children list */
	m_parent = i_newParent;

	if (m_parent) //parent could be null
	{
		m_parent->addChild(this);
	}

}


/************************************************************************/
/* PRIVATE                                                              */
/************************************************************************/
void GameObject::addChild(GameObject* i_gameObj)
{
	if (i_gameObj)
	{
		m_children.push_back(i_gameObj);
	}
	
}

void GameObject::removeChild(GameObject* i_gameObj)
{
	if (i_gameObj)
	{
		/* remove child from children list */
		std::vector<GameObject*>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (*it == i_gameObj)
			{
				m_children.erase(it);
				return;
			}
		}
	}
}