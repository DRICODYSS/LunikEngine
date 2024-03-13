#pragma once

#define USE_STL_VECTOR 1
#define USE_STL_DEQUE  1

#if USE_STL_VECTOR
#include <vector>
namespace Lunik::utils
{
	template<typename T>
	using d_array = std::vector<T>;
}
#endif

#if USE_STL_DEQUE
#include <deque>
namespace Lunik::utils
{
	template<typename T>
	using deque = std::deque<T>;
}
#endif

namespace Lunik::utils
{
	// TODO For My implement our own containers
	//template<typename T>
	//class d_array {};
}