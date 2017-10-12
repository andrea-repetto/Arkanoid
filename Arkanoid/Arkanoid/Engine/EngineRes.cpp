#include "pch.h"
#include "EngineRes.h"


using namespace Engine;

std::shared_ptr<DX::DeviceResources> EngineRes::DeviceResources = nullptr;

EngineRes::EngineRes()
{
}


EngineRes::~EngineRes()
{
}



void EngineRes::Initialize(const std::shared_ptr<DX::DeviceResources>& deviceResources )
{
	EngineRes::DeviceResources = deviceResources;
}


const std::shared_ptr<DX::DeviceResources>& EngineRes::GetDeviceResource()
{
	return EngineRes::DeviceResources;
}

