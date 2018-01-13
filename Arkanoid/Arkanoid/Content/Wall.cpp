#include "pch.h"
#include "Wall.h"
#include "Brick.h"
#include "GameIDs.h"

/* WALL/ BRICKS MANAGER */

using namespace Engine;
using namespace DirectX;

const float Wall::BRICK_PADDING = 0.1f;

Wall::Wall()
	: GameObject()
	, m_bricksOnScree(0)
{
	m_WallMaterials[GREY_ROW_IDX] = Engine::Material(0.63f, 0.63f, 0.63f);
	m_WallMaterials[RED_ROW_IDX] = Engine::Material(1.0f, 0.0f, 0.0f);
	m_WallMaterials[YELLOW_ROW_IDX] = Engine::Material(1.0f, 1.0f, 0.0f);
	m_WallMaterials[BLUE_ROW_IDX] = Engine::Material(0.0f, 0.0f, 1.0f);
	m_WallMaterials[FUXIA_ROW_IDX] = Engine::Material(1.0f, 0.0f, 1.0f);
	m_WallMaterials[GREEN_ROW_IDX] = Engine::Material(0.0f, 1.0f, 0.0f);

	for (size_t idx = 0; idx < WALL_HEIGHT; ++idx)
	{
		for (size_t jdx = 0; jdx < WALL_WIDTH; ++jdx)
		{
			Brick* brick = new Brick();
			if (idx == (WALL_HEIGHT-1))
			{
				brick->SetLife(2);
			}
			brick->SetParent(this);

			float startPosition_X = -(brick->GetWidth() * (WALL_WIDTH - 1) / 2 + brick->GetWidth() / 2 + BRICK_PADDING * (1+(WALL_WIDTH - 1) / 2));
			float startPosition_Y = -(brick->GetHeight() * (WALL_HEIGHT - 1) / 2 + brick->GetHeight() / 2 + BRICK_PADDING * (1 + (WALL_HEIGHT - 1) / 2));

			float position_X = startPosition_X + BRICK_PADDING + jdx*brick->GetWidth() + jdx*BRICK_PADDING;
			float position_Y = startPosition_Y + BRICK_PADDING + idx*brick->GetHeight() + idx*BRICK_PADDING;

			brick->SetLocalPosition(XMFLOAT3(position_X, position_Y, 0.0f));

			brick->SetMaterial(m_WallMaterials[WALL_HEIGHT-1 - idx]);

			m_BrickList.push_back(brick);

			brick->RegisterForEvents(this);

			++m_bricksOnScree;
		}
	}

}


Wall::~Wall()
{
	for (size_t idx = 0; idx < m_BrickList.size(); ++idx)
	{
		m_BrickList[idx]->UnregisterFromEvents(this);

		delete m_BrickList[idx];
	}
}


void Wall::doStart()
{
	for (size_t idx = 0; idx < m_BrickList.size(); ++idx)
	{
		m_BrickList[idx]->Start();
	}
}

void Wall::doUpdate(DX::StepTimer const& timer)
{
	for (size_t idx = 0; idx < m_BrickList.size(); ++idx)
	{
		m_BrickList[idx]->Update(timer);
	}
}

void Wall::doRender()
{
	for (size_t idx = 0; idx < m_BrickList.size(); ++idx)
	{
		m_BrickList[idx]->Render();
	}
}


void Wall::OnEvent(GameObject* src, int event, GameObject* data)
{
	GameObject::OnEvent(src, event, data);

	if (event == GameData::EVE_BRICK_HIT)
	{
		Brick* brick = reinterpret_cast<Brick*>(src);
		int brickLife = brick->GetLife() - 1;
		brick->SetLife(brickLife);

		if (brickLife <= 0)
		{
			brick->SetEnable(false);
			--m_bricksOnScree;

			if (m_bricksOnScree == 0)
			{
				NotifyEvent(GameData::EVE_WALL_IS_EMPTY, nullptr);
			}
		}
		else
		{
			/* Make color darker */
			Engine::Material material = brick->GetMaterial();
			material.color.x -= 0.2f;
			material.color.y -= 0.2f;
			material.color.z -= 0.2f;
			brick->SetMaterial(material);
		}

	}
}
