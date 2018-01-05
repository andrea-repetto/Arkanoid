#pragma once

#include "Engine\PhysicsObject.h"
#include <vector>

namespace Engine
{
	namespace Physics
	{
		class Octree
		{
		public:
			Octree(BoundingBox boundingBox);
			~Octree();

			void Clear();

			static Octree* BuildOctree(BoundingBox max, BoundingBox min);

		private:
			static void RecursiveCreateChildren(Octree& parent, BoundingBox min);

		private:
			enum
			{
				FRONT_UPPER_LEFT	= 0,		
				FRONT_UPPER_RIGHT,
				FRONT_DOWN_LEFT,
				FRONT_DOWN_RIGHT,
				BACK_UPPER_LEFT,
				BACK_UPPER_RIGHT,
				BACK_DOWN_LEFT,
				BACK_DOWN_RIGHT
			};

		private:
			BoundingBox							m_BoundingBox;
			Octree								*m_Children[8];
			std::vector<PhysicsObject*>			m_PhysicsObjectList;


		};
	}
}

