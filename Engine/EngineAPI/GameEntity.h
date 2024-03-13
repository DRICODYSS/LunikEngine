#pragma once

#include "..\Components\ComponentCommon.h"
#include "TransformComponent.h"

namespace Lunik::GameEntity
{
	DEFINE_TYPED_ID(Entity_id);

	class Entity final
	{
	public:
		constexpr          Entity() : id{ ID::Invalid_ID } {}
		constexpr explicit Entity(Entity_id id_new) : id{ id_new } {}

		constexpr Entity_id GetID() const { return id; }
		const bool IsValid() const { return ID::IsValid(id); }

		Transform::Component GetTransform() const;
	private:
		Entity_id id;
	};
}