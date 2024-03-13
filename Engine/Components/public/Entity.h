#pragma once

#include "..\ComponentCommon.h"

namespace Lunik
{
#define INIT_INFO(Component) namespace Component { struct InitInfo; }

INIT_INFO(Transform);

#undef INIT_INFO

	namespace GameEntity
	{
		struct FEntityInfo
		{
			Transform::InitInfo* Transform{ nullptr };
		};

		Entity CreateEntity(const FEntityInfo&);
		void RemoveEntity(Entity);
		bool IsValid(Entity);
	}
}
