#pragma once
namespace GameData
{
	enum OBJ_IDS
	{
		ID_UKNOWN	= -1,
		ID_BRICK	= 0,
		ID_BALL	= 1,
		ID_PLAYER  = 2,
		ID_SIDE_WALL	= 3 
	};

	enum EVENTS
	{
		EVE_UKNOWN		= -1,
		EVE_BRICK_HIT	= 0,
		EVE_PLAYER_HITs	= 1
	};
}