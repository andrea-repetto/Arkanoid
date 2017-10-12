#pragma once

/** Forward Declarations */
namespace DX
{
	class StepTimer;
}

namespace Engine
{

	class Square
	{
	public:
		Square();
		~Square();

		void Update(DX::StepTimer const& timer);
		void Render();
	};

}

