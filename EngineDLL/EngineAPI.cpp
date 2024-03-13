
#ifndef EDITOR_INTERFACE
#define EDITOR_INTERFACE extern "C" __declspec(dllexport)
#endif // !EDITOR_INTERFACE

#include "CommonHeaders.h"
#include "Id.h"
#include "..\Engine\Components\public\Entity.h"
#include "..\Engine\Components\public\Transform.h"

using namespace Lunik;

namespace
{
	struct TransformComp
	{
		float position[3];
		float rotation[3];
		float scale[3];

		Transform::InitInfo ToInitInfo()
		{
			using namespace DirectX;
			Transform::InitInfo Info{};
			memcpy(&Info.position[0], &position[0], sizeof(float) * _countof(position));
			memcpy(&Info.scale[0], &scale[0], sizeof(float) * _countof(scale));
			XMFLOAT3A rot{ &rotation[0] };
			XMVECTOR quat{ XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3A(&rot)) };
			XMFLOAT4A rot_quat{};
			XMStoreFloat4A(&rot_quat, quat);
			memcpy(&Info.rotation[0], &rot_quat.x, sizeof(float) * _countof(Info.rotation));
			return Info;
		}
	};

	struct GameEntity_Descriptor
	{
		TransformComp transform;
	};

	GameEntity::Entity EntityFromID(ID::id_type id)
	{
		return GameEntity::Entity{ GameEntity::Entity_id{id} };
	}
	
}


EDITOR_INTERFACE ID::id_type CreateGameEntity(GameEntity_Descriptor* entity)
{
	assert(entity);
	GameEntity_Descriptor& desc{ *entity };
	Transform::InitInfo TransformInfo{ desc.transform.ToInitInfo() };
	GameEntity::FEntityInfo EntityInfo{ .Transform = &TransformInfo };
	return GameEntity::CreateEntity(EntityInfo).GetID();
}

EDITOR_INTERFACE void RemoveGameEntity(ID::id_type id)
{
	assert(ID::IsValid(id));
	GameEntity::RemoveEntity(EntityFromID(id));
}