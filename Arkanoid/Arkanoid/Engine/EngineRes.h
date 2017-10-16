#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\DirectXHelper.h"

namespace Engine
{
	class EngineRes
	{
	public:
		static EngineRes* Instance();
		static void Initialize( const std::shared_ptr<DX::DeviceResources>& );
		static const std::shared_ptr<DX::DeviceResources>& GetDeviceResource();

	private:
		EngineRes();
		~EngineRes();
		EngineRes(const EngineRes&);
		EngineRes& operator=(const EngineRes&);


	private:
		static std::shared_ptr<DX::DeviceResources> DeviceResources;
	};
}

