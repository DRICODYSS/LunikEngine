#pragma once
#include "CommonHeaders.h"

namespace Lunik::Math
{
	inline constexpr float PI = 3.1415926535897932384626433832795f;
	inline float EPSILON = 1e-5f;

#if defined(_WIN64)
	using Vector2D     = DirectX::XMFLOAT2;
	using Vector2D_A   = DirectX::XMFLOAT2A;
	using Vector       = DirectX::XMFLOAT3;
	using Vector_A     = DirectX::XMFLOAT3A;
	using Vector4D     = DirectX::XMFLOAT3;
	using Vector4D_A   = DirectX::XMFLOAT3A;

	using Vector2D_ui  = DirectX::XMUINT2;
	using Vector_ui    = DirectX::XMUINT3;
	using Vector4D_ui  = DirectX::XMUINT4;
	using Vector2D_i   = DirectX::XMINT2;
	using Vector_i     = DirectX::XMINT3;
	using Vector4D_i   = DirectX::XMINT4;

	using Matrix_3X3   = DirectX::XMFLOAT3X3;
	using Matrix_4X4   = DirectX::XMFLOAT4X4;
	using Matrix_4X4_A = DirectX::XMFLOAT4X4A;

#endif // defined(_WIN64)

}