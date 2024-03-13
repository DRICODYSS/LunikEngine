#include "..\public\Entity.h"
#include "..\public\Transform.h"

namespace Lunik::GameEntity
{
	namespace
	{
		utils::d_array<Transform::Component> Transforms;

		utils::d_array<ID::generation_type>  Generations;
		utils::deque<Entity_id>              Free_IDs;
	}

	Entity CreateEntity(const FEntityInfo& Info)
	{
		assert(Info.Transform); // All Game Entity must have a Transform Component
		if (!Info.Transform) return Entity{};

		Entity_id id;
		if (Free_IDs.size() > ID::MinDeletedElements)
		{
			id = Free_IDs.front();
			assert(!IsValid(Entity{ id }));
			Free_IDs.pop_front();
			id = Entity_id{ ID::NewGeneration(id) };
			++Generations[ID::Index(id)];
		}
		else
		{
			id = Entity_id{ static_cast<ID::id_type>(Generations.size()) };
			Generations.push_back(0);

			Transforms.emplace_back(); //TODO
		}

		const Entity NewEntity{ id };
		const ID::id_type index{ ID::Index(id) };

		// Create Transform component
		assert(!Transforms[index].IsValid());
		Transforms[index] = Transform::CreateTransform(*Info.Transform, NewEntity);
		if (!Transforms[index].IsValid())
		{
			return {};
		}

		return NewEntity;
	}

	void RemoveEntity(Entity entity)
	{
		const Entity_id id{ entity.GetID() };
		const ID::id_type index{ ID::Index(id) };
		assert(IsValid(entity));

		if (IsValid(entity))
		{
			Transform::RemoveTransform(Transforms[index]);
			Transforms[index] = {};
			Free_IDs.push_back(id);
		}
	}

	bool IsValid(Entity entity)
	{
		assert(entity.IsValid());
		const Entity_id id{ entity.GetID() };
		const ID::id_type index{ ID::Index(id) };
		assert(index < Generations.size());
		assert(Generations[index] == ID::Generation(id));
		return Generations[index] == ID::Generation(id) && Transforms[index].IsValid();
	}

	/* Engine API - GameEntity */
	Transform::Component Entity::GetTransform() const
	{
		assert(GameEntity::IsValid(*this));
		const ID::id_type index{ ID::Index(id) };
		return Transforms[index];
	}
}

