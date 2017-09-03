#pragma once

#include <vector>

namespace GameEngine
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void Update();
		void Render();

	private:


		virtual void DoUpdate() = 0;
		virtual void DoRender() = 0;

		void AttachTo(GameObject *);
		void DetachFrom(GameObject *);

		std::vector<GameObject* > m_ChildNodes;
		GameObject* m_ParentNode;


	};
}

