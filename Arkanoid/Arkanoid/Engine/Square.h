#pragma once

#include "GameObject.h"

#include "RenderObject.h"



namespace Engine
{

	class Square: public GameObject
	{
	public:
		Square();
		~Square();

	private:
		void doStart() override;
		void doUpdate(DX::StepTimer const& timer) override;
		void doRender() override;

	private:
		RenderObject* m_square;
		GeometryGenerator::MeshData m_meshData;
		//RenderObject m_square2;


	};

}

