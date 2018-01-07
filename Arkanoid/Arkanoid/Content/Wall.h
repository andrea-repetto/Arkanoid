#pragma once
#include "Engine\GameObject.h"
#include "Engine\RenderObject.h"

#include <vector>

class Brick;

class Wall : public Engine::GameObject
{
public:
	explicit Wall();
	~Wall();

protected:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

private:
	enum WallSize
	{
		GREY_ROW_IDX = 0,
		RED_ROW_IDX = 1,
		YELLOW_ROW_IDX = 2,
		BLUE_ROW_IDX = 3,
		FUXIA_ROW_IDX = 4,
		GREEN_ROW_IDX = 5,
		WALL_HEIGHT	= 6,
		WALL_WIDTH	= 13 /* This number should be odd */
	};

private:
	Engine::Material m_WallMaterials[WALL_HEIGHT];
	std::vector<Brick*> m_BrickList;

	static const float BRICK_PADDING;
	
};

