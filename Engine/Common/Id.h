#pragma once

#include "CommonHeaders.h"

namespace Lunik::ID
{
	using id_type = uint_32;

	namespace INTERNAL
	{
		 inline constexpr uint_32 generation_bits{ 10 };
		 inline constexpr uint_32 index_bits{ sizeof(id_type) * 8 - generation_bits };

		 inline constexpr id_type generation_mask{ (id_type{1} << generation_bits) - 1 };
		 inline constexpr id_type index_mask{ (id_type{1} << index_bits) - 1 };
	}

	inline constexpr id_type Invalid_ID{ static_cast<id_type>(-1) };
	inline constexpr uint_32 MinDeletedElements{ 1024 };

	using generation_type = std::conditional_t<INTERNAL::generation_bits <= 16, std::conditional_t<INTERNAL::generation_bits <= 8, uint_8, uint_16>, uint_32>;

	static_assert(sizeof(generation_type) * 8 >= INTERNAL::generation_bits);
	static_assert(sizeof(id_type) - sizeof(generation_type) > 0);

	inline bool IsValid(id_type id)
	{
		return id != Invalid_ID;
	}

	inline id_type Index(id_type id)
	{
		id_type index{ id & INTERNAL::index_mask };
		assert(index != INTERNAL::index_mask);
		return index;
	}

	inline id_type Generation(id_type id)
	{
		return (id >> INTERNAL::index_bits) & INTERNAL::generation_mask;
	}

	inline id_type NewGeneration(id_type id)
	{
		const id_type generation{ ID::Generation(id) + 1 };
		assert(generation <  ((static_cast<uint_64>(1) << INTERNAL::generation_bits) - 1));
		return Index(id) | (generation << INTERNAL::index_bits);
	}

#if _DEBUG
	namespace internal
	{
		struct Base_id
		{
			constexpr explicit Base_id(id_type id) : _id{ id } {}
			constexpr operator id_type() const { return _id; }

		private:
			id_type _id;
		};
	}
#define DEFINE_TYPED_ID(name)												\
		struct name final : ID::internal::Base_id							\
		{																	\
			constexpr explicit name(ID::id_type id) : Base_id{ id } {}		\
			constexpr		   name() : Base_id{ 0 } {}						\
		};																	
#else

#define DEFINE_TYPED_ID(name) using name = ID::id_type;

#endif
}