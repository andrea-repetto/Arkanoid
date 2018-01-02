#include "pch.h"
#include "QuadTree.h"

using namespace Engine::Physics;

const int QuadTree::MAX_LEVEL = 5;


QuadTree::QuadTree(int level, Bounds bounds)
	: m_Level(level)
	, m_Bounds(bounds)
{
	for (int idx = 0; idx < NODES_NUMBER; ++idx)
	{
		m_Nodes[idx] = nullptr;
	}
}


QuadTree::~QuadTree()
{
	for (int idx = 0; idx < NODES_NUMBER; ++idx)
	{
		delete m_Nodes[idx];
	}
}


void QuadTree::Clear()
{
	m_Objects.clear();
}


void QuadTree::split()
{
	float subWidth = m_Bounds.width / 2.0f;
	float subHeight = m_Bounds.heigth / 2.0f;
	float x = m_Bounds.x;
	float y = m_Bounds.y;

	m_Nodes[0] = new QuadTree(m_Level + 1, Bounds(x + subWidth, y, subWidth, subHeight));
	m_Nodes[1] = new QuadTree(m_Level + 1, Bounds(x, y, subWidth, subHeight));
	m_Nodes[2] = new QuadTree(m_Level + 1, Bounds(x, y + subHeight, subWidth, subHeight));
	m_Nodes[3] = new QuadTree(m_Level + 1, Bounds(x + subWidth, y + subHeight, subWidth, subHeight));

}
