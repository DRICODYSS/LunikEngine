#include "..\public\Transform.h"

namespace Lunik::Transform
{
	namespace
	{
		utils::d_array<Math::Vector> Positions;
		utils::d_array<Math::Vector4D> Rotations;
		utils::d_array<Math::Vector> Scales;
	}

	Component CreateTransform(const InitInfo& Info, GameEntity::Entity entity)
	{
		assert(entity.IsValid());
		const ID::id_type EntityIndex{ ID::Index(entity.GetID()) };

		if (Positions.size() > EntityIndex)
		{
			Positions[EntityIndex] = static_cast<Math::Vector>(Info.position);
			Rotations[EntityIndex] = static_cast<Math::Vector4D>(Info.rotation);
			Scales[EntityIndex]    = static_cast<Math::Vector>(Info.scale);
		}
		else
		{
			assert(Positions.size() == EntityIndex);
			Positions.emplace_back(Info.position);
			Rotations.emplace_back(Info.rotation);
			Scales.emplace_back(Info.scale);
		}
		return Component(Transform_id{ static_cast<ID::id_type>(Positions.size() - 1) });
	}

	void RemoveTransform(Component transform)
	{
		assert(transform.IsValid());
	}

	/* Engine API - Transform Component */
	Math::Vector Component::GetPosition() const
	{
		assert(IsValid());
		return Positions[ID::Index(this->id)];
	}
	Math::Vector4D Component::GetRotation() const
	{
		assert(IsValid());
		return Rotations[ID::Index(this->id)];
	}
	Math::Vector Component::GetScale() const
	{
		assert(IsValid());
		return Scales[ID::Index(this->id)];
	}
}
