// Copyright (c) Daniel Ekimov
// Distributed under the MIT license. See the LICENSE file in the project root for more information.

#pragma once

#include <stdint.h>

#pragma region unsigned integers

using uint_8  = uint8_t;
using uint_16 = uint16_t;
using uint_32 = uint32_t;
using uint_64 = uint64_t;

inline constexpr uint_8  uint_8_invalid_id { 0xffui8 };
inline constexpr uint_16 uint_16_invalid_id{ 0xffffui16 };
inline constexpr uint_32 uint_32_invalid_id{ 0xffff'ffffui32 };
inline constexpr uint_64 uint_64_invalid_id{ 0xffff'ffff'ffff'ffffui64 };

#pragma endregion

#pragma region integers

using int_8  = int8_t;
using int_16 = int16_t;
using int_32 = int32_t;
using int_64 = int64_t;

#pragma endregion