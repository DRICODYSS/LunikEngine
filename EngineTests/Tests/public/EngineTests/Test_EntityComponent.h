#pragma once
// C++
#include <iostream>
#include <ctime>

// Engine Headers
#include "..\..\ITest.h"
#include "..\..\..\..\Engine\Components\public\Entity.h"
#include "..\..\..\..\Engine\Components\public\Transform.h"

namespace EngineTests
{
	using namespace Lunik;

	class Test_EntityComponent final : public ITest
	{
	public:
		bool Init() override;
		void Run() override;
		void Shutdown() override {}

		void Print_result();

	private:
		utils::d_array<GameEntity::Entity> TEntities;

		uint_32 added_{ 0 };
		uint_32 removed_{ 0 };
		uint_32 num_entities_{ 0 };

		void Create_rand();
		void Remove_rand();
	};
}


