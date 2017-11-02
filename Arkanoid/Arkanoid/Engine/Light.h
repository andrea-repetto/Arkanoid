#pragma once
#include <DirectXMath.h>
namespace Engine
{
	struct DirectionalLight
	{
		DirectX::XMFLOAT4 Direction;
		DirectX::XMFLOAT4 Strenght;
	};

	struct AmbientLight
	{
		DirectX::XMFLOAT4 Strenght;
	};
}