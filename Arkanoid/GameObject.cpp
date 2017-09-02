#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
{
	m_ParentNode = nullptr;
	
}


GameObject::~GameObject()
{
	m_ParentNode = nullptr;
	
	for (size_t i = 0; i < m_ChildNodes.size(); ++i)
	{
		delete m_ChildNodes[i];
	}
}

void GameObject::AttachTo(GameObject *i_Parent)
{
	/* Detach this node from previous parent */
	DetachFrom(m_ParentNode);

	m_ParentNode = i_Parent;
	i_Parent->m_ChildNodes.push_back(this);
}

void GameObject::DetachFrom(GameObject* i_Parent)
{
	if (i_Parent != nullptr)
	{
		for (size_t i = 0; i < i_Parent->m_ChildNodes.size(); ++i)
		{
			if (i_Parent->m_ChildNodes[i] == this)
			{
				i_Parent->m_ChildNodes.erase(i_Parent->m_ChildNodes.begin() + i);
				return;
			}
		}
	}
}

void GameObject::Update()
{
	DoUpdate();

	for (size_t i=0; i<m_ChildNodes.size(); ++i)
	{
		m_ChildNodes[i]->Update();
	}
}

void GameObject::Render()
{
	DoRender();

	for (size_t i = 0; i<m_ChildNodes.size(); ++i)
	{
		m_ChildNodes[i]->Render();
	}
}

