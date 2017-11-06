#include "pch.h"
#include "Square.h"
#include "GameEngine.h"

#include "Common\d3dUtil.h"
#include "Common\StepTimer.h"

#include "Camera.h"

#include <ppltasks.h>
#include <synchapi.h>

#include "Common\GeometryGenerator.h"
#include "Common\Keyboard.h"
#include <iostream>



using namespace Engine;

using namespace Concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Storage;

Square::Square()
	: GameObject()
{
	//TODO FIX memoery leak
	GeometryGenerator geoGen;
	GeometryGenerator::MeshData m_meshData = geoGen.CreateSphere(1, 8, 4);
	//m_meshData = geoGen.CreateCylinder(1, 1, 1, 32, 16);
	//m_meshData = geoGen.CreateBox(1, 1, 1, 0);

	UINT vertexBufferSize = m_meshData.Vertices.size();

	Vertex* cubeVertices = new Vertex[vertexBufferSize];

	for (UINT idx = 0; idx < vertexBufferSize; ++idx)
	{
		GeometryGenerator::Vertex v = m_meshData.Vertices[idx];


		cubeVertices[idx] = { v.Position, XMFLOAT3(v.Normal.x, v.Normal.y, v.Normal.z) };
	}

	UINT indexBufferSize = m_meshData.Indices32.size();

	unsigned short* cubeIndices = new unsigned short[indexBufferSize];

	for (UINT idx = 0; idx < indexBufferSize; ++idx)
	{
		cubeIndices[idx] = m_meshData.Indices32[idx];
	}

	m_square = new RenderObject(cubeVertices, vertexBufferSize, cubeIndices, indexBufferSize);

	m_square->SetParent(this);

}

Square::~Square()
{
	delete m_square;
}


void Square::doStart()
{
	m_square->Start();
	//m_square2.Start();
	//XMFLOAT3 pos = m_square2->GetLocalTransform();
//	pos.x -= 1;

//	m_square2.SetLocalTransform(pos);

}

void Square::doUpdate(DX::StepTimer const& timer)
{


	auto kb = DirectX::Keyboard::Get().GetState();

	if (kb.W)
	{
		std::cout << "Premuto W" << std::endl;
	}
		// W key is down

	
	XMFLOAT3 rot = this->GetLocalRotationYawPitchRoll();
	XMFLOAT3 pos = this->GetLocalTransform();
	pos.z += timer.GetElapsedSeconds()*0.1;
	//pos.y += timer.GetElapsedSeconds()*0.1;
	//pos.z += timer.GetElapsedSeconds()*0.1;
	XMFLOAT3 scale = this->GetLocalScale();
	scale.x = 0.25f;
	scale.y = 0.25f;
	scale.z = 0.25f;
	this->SetLocalScale(scale);
	//pos.x += timer.GetElapsedSeconds();
	rot.x+= timer.GetElapsedSeconds()*2;
//	pos.y += timer.GetElapsedSeconds();
	this->SetLocalRotationYawPitchRoll(rot);
	//this->SetLocalTransform(pos);
	//TODO remove
	// Update the constant buffer resource.
	

	m_square->Update(timer);
	//m_square2.Update(timer);

}

void Square::doRender()
{
	m_square->Render();
//	m_square2.Render();

}
