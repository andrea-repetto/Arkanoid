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
			explicit Octree(BoundingBox boundingBox);
			~Octree();

			static Octree* BuildOctree(BoundingBox max, BoundingBox min);
			static void UpdateOctree(Octree& root);
			static void RegisterPhysicsObj(PhysicsObject& phyObj);
			static void DeregisterPhysicsObj(PhysicsObject& phyObj);
			static void RunCollisionDetection(Octree& root);

		private:
			static void RecursiveCreateChildren(Octree& parent, BoundingBox min);

			void Clear();
			void Insert(PhysicsObject& phyObj);
			int GetIndex(PhysicsObject& phyObj);
			void RetrievePossibleCollisionObject(std::vector<PhysicsObject*>& result, PhysicsObject& obj);

		private:
			enum
			{
				PARENT_NODE			= -1,
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
			static std::vector<PhysicsObject*>	AllPhysicsObjList;

		private:
			BoundingBox							m_BoundingBox;
			Octree								*m_Children[8];
			std::vector<PhysicsObject*>			m_PhysicsObjectList;


		};
	}
}

