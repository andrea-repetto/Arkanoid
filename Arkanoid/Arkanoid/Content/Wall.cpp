#include "pch.h"
#include "Wall.h"
#include "Brick.h"

using namespace Engine;
using namespace DirectX;

const float Wall::BRICK_PADDING = 0.1f;

Wall::Wall()
	: GameObject()
{
	m_WallMaterials[GREY_ROW_IDX] = Engine::Material(0.63f, 0.63f, 0.63f);
	m_WallMaterials[RED_ROW_IDX] = Engine::Material(1.0f, 0.0f, 0.0f);
	m_WallMaterials[YELLOW_ROW_IDX] = Engine::Material(1.0f, 1.0f, 0.0f);
	m_WallMaterials[BLUE_ROW_IDX] = Engine::Material(0.0f, 0.0f, 1.0f);
	m_WallMaterials[FUXIA_ROW_IDX] = Engine::Material(1.0f, 0.0f, 1.0f);
	m_WallMaterials[GREEN_ROW_IDX] = Engine::Material(0.0f, 1.0f, 0.0f);

	for (int idx = 0; idx < WALL_HEIGHT; ++idx)
	{
		for (int jdx = 0; jdx < WALL_WIDTH; ++jdx)
		{
			Brick* brick = new Brick();
			brick->SetParent(this);

			float startPosition_X = -(brick->GetWidth() * (WALL_WIDTH - 1) / 2 + brick->GetWidth() / 2 + BRICK_PADDING * (1+(WALL_WIDTH - 1) / 2));
			float startPosition_Y = -(brick->GetHeight() * (WALL_HEIGHT - 1) / 2 + brick->GetHeight() / 2 + BRICK_PADDING * (1 + (WALL_HEIGHT - 1) / 2));

			float position_X = startPosition_X + BRICK_PADDING + jdx*brick->GetWidth() + jdx*BRICK_PADDING;
			float position_Y = startPosition_Y + BRICK_PADDING + idx*brick->GetHeight() + idx*BRICK_PADDING;

			brick->SetLocalPosition(XMFLOAT3(position_X, position_Y, 0.0f));

			brick->SetMaterial(m_WallMaterials[WALL_HEIGHT-1 - idx]);

			m_BrickList.push_back(brick);
		}
	}

}


Wall::~Wall()
{
	for (int idx = 0; idx < m_BrickList.size(); ++idx)
	{
		delete m_BrickList[idx];
	}
}


void Wall::doStart()
{
	for (int idx = 0; idx < m_BrickList.size(); ++idx)
	{
		m_BrickList[idx]->Start();
	}
}

void Wall::doUpdate(DX::StepTimer const& timer)
{
	for (int idx = 0; idx < m_BrickList.size(); ++idx)
	{
		m_BrickList[idx]->Update(timer);
	}
}

void Wall::doRender()
{
	for (int idx = 0; idx < m_BrickList.size(); ++idx)
	{
		m_BrickList[idx]->Render();
	}
}
