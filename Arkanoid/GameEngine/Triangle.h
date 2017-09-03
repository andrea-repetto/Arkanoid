#pragma once
#include "GameObject.h"

namespace GameEngine
{
	class Triangle: public GameObject
	{
	public:
		Triangle();
		virtual ~Triangle();

	private:
		void DoUpdate() override;
		void DoRender() override;
	};
}

