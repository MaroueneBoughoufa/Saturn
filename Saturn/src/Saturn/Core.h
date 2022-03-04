#pragma once

#ifdef ST_PLATFORM_WINDOWS
	#ifdef ST_DYNAMIC_LINK
		#ifdef _MSC_VER
			#ifdef ST_BUILD_DLL
				#define SATURN_API __declspec(dllexport)
			#else
				#define SATURN_API __declspec(dllimport)
			#endif
		#endif
	#else
		#define SATURN_API
	#endif
#endif

#ifdef ST_PLATFORM_LINUX
	#ifdef __GNUC__
		#ifdef ST_EXPORT
			#define SATURN_API __attribute__((visibility("default")))
		#else
			#define SATURN_API
		#endif
	#endif
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
