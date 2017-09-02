#pragma once

#include <vector>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

private:
	void Update();
	void Render();

	virtual void DoUpdate() = 0;
	virtual void DoRender() = 0;

	void AttachTo(GameObject *);
	void DetachFrom(GameObject *);

	std::vector<GameObject* > m_ChildNodes;
	GameObject* m_ParentNode;


};

