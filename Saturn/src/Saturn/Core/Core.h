#pragma once

#include <memory>

#ifdef ST_DYNAMIC_LINK
	#ifdef _MSC_VER
		#ifdef ST_BUILD_DLL
			#define SATURN_API __declspec(dllexport)
		#else
			#define SATURN_API __declspec(dllimport)
		#endif
	#elif defined __GNUC__
		#ifdef ST_EXPORT
			#define SATURN_API __attribute__((visibility("default")))
		#endif
	#endif
#else
	#define SATURN_API
#endif

#ifdef ST_ENABLE_ASSERT
	#define ST_ASSERT(x, ...) { if(!(x)) { ST_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ST_CORE_ASSERT(x, ...) { if(!(x)) { ST_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ST_ASSERT(x, ...)
	#define ST_CORE_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) (1 << x)


namespace Saturn
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
