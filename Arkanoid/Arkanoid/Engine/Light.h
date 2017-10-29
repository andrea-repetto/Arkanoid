#pragma once
#include <DirectXMath.h>
namespace Engine
{
	struct DirectionalLight
	{
		DirectX::XMFLOAT3 Direction;
		DirectX::XMFLOAT3 Strenght;
	};

	struct AmbientLight
	{
		DirectX::XMFLOAT3 Strenght;
	};
}