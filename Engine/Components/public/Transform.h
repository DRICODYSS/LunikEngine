#pragma once

#include "..\ComponentCommon.h"

namespace Lunik::Transform
{
	struct InitInfo
	{
		float position[3]{};
		float rotation[4]{};
		float scale[3]{1.0, 1.0, 1.0};
	};

	Component CreateTransform(const InitInfo& Info, GameEntity::Entity entity);
	void RemoveTransform(Component transform);
}
