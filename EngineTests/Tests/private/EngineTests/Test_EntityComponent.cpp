#include "..\..\public\EngineTests\Test_EntityComponent.h"

bool EngineTests::Test_EntityComponent::Init()
{
	srand(static_cast<uint_32>(time(nullptr)));
	return true;
}

void EngineTests::Test_EntityComponent::Run()
{
	do
	{
		for (uint_32 i = 0; i < 10000; ++i)
		{
			Create_rand();
			Remove_rand();
			num_entities_ = static_cast<uint_32>(TEntities.size());
		}
		Print_result();
	} while (getchar() != 'q');
}

void EngineTests::Test_EntityComponent::Print_result()
{
	std::cout << "Entity Created: " << added_ << "\n"
			  << "Entity Removed: " << removed_ << "\n";
}


void EngineTests::Test_EntityComponent::Create_rand()
{
	uint_32 count = rand() % 20;
	if (TEntities.empty()) count = 1000;
	Transform::InitInfo TransformInfo{};
	GameEntity::FEntityInfo EntityInfo{ .Transform = &TransformInfo };
	while (count > 0)
	{
		++added_;
		GameEntity::Entity entity{ GameEntity::CreateEntity(EntityInfo) };
		assert(entity.IsValid() && ID::IsValid(entity.GetID()));
		TEntities.push_back(entity);
		assert(GameEntity::IsValid(entity));
		--count;
	}
}

void EngineTests::Test_EntityComponent::Remove_rand()
{
	uint_32 count = rand() % 20;
	if (TEntities.size() < 1000) return;
	Transform::InitInfo TransformInfo{};
	GameEntity::FEntityInfo EntityInfo{ .Transform = &TransformInfo };
	while (count > 0)
	{
		++removed_;
		const uint_32 index{ static_cast<uint_32>(rand()) % static_cast<uint_32>(TEntities.size()) };
		const GameEntity::Entity entity{ TEntities[index] };
		assert(entity.IsValid() && ID::IsValid(entity.GetID()));
		if (entity.IsValid())
		{
			GameEntity::RemoveEntity(entity);
			TEntities.erase(TEntities.begin() + index);
			assert(!GameEntity::IsValid(entity));
		}
		--count;
	}
}
