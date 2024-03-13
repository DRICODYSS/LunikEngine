#pragma once

#include "../Components/ComponentCommon.h"

namespace Lunik::Transform
{
	DEFINE_TYPED_ID(Transform_id)

	class Component final
	{
	public:
		constexpr          Component() : id{ ID::Invalid_ID } {}
		constexpr explicit Component(Transform_id id_new) : id{ id_new } {}

		constexpr Transform_id GetID() const { return id; }
		const bool IsValid() const { return ID::IsValid(id); }

		Math::Vector   GetPosition() const;
		Math::Vector4D GetRotation() const;
		Math::Vector   GetScale() const;

	private:
		Transform_id id;
	};
}