#pragma once

#ifdef Rtro_PLATFORM_WINDOWS
	#ifdef Rtro_DYNAMIC_LINK
		#ifdef _MSC_VER
			#ifdef Rtro_BUILD_DLL
				#define RETRO_API __declspec(dllexport)
			#else
				#define RETRO_API __declspec(dllimport)
			#endif
		#endif
	#else
		#define RETRO_API
	#endif
#endif

#ifdef Rtro_PLATFORM_LINUX
	#ifdef __GNUC__
		#ifdef Rtro_EXPORT
			#define RETRO_API __attribute__((visibility("default")))
		#endif
	#endif
#endif

#ifdef Rtro_ENABLE_ASSERT
	#define Rtro_ASSERT(x, ...) { if(!(x)) { Rtro_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define Rtro_CORE_ASSERT(x, ...) { if(!(x)) { Rtro_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define Rtro_ASSERT(x, ...)
	#define Rtro_CORE_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) (1 << x)
