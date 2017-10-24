#include "pch.h"
#include "Square.h"
#include "GameEngine.h"

#include "Common\d3dUtil.h"
#include "Common\StepTimer.h"

#include "Camera.h"

#include <ppltasks.h>
#include <synchapi.h>

using namespace Engine;

using namespace Concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Storage;

Square::Square()
	: GameObject()
{
	m_square.SetParent(this);
}

Square::~Square()
{

}


void Square::doStart()
{
	m_square.Start();

}

void Square::doUpdate(DX::StepTimer const& timer)
{
/**	
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
	rot.z+= timer.GetElapsedSeconds()*2;
//	pos.y += timer.GetElapsedSeconds();
	this->SetLocalRotationYawPitchRoll(rot);
	this->SetLocalTransform(pos);
	//TODO remove
	// Update the constant buffer resource.
	*/

	m_square.Update(timer);

}

void Square::doRender()
{
	m_square.Render();


}
