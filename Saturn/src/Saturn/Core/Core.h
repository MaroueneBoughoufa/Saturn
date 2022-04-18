#pragma once

#include <memory>

// Platform Detection
#ifdef _WIN32
	#ifdef _WIN64
		#define ST_PLATFORM_WINDOWS
	#else
		#error "x86 builds are not supported"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	* so we must check all of them (in this order)
	* to ensure that we're running on MAC
	* and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define ST_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define ST_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined (__ANDROID__)
	#define ST_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined (__linux__)
	#define ST_PLATFORM_LINUX
	#error "Android is not supported!"
#endif
// End Platform detection


// DLL support
#ifdef ST_DYNAMIC_LINK
	#ifdef _MSC_VER
		#ifdef ST_BUILD_DLL
			#define SATURN_API __declspec(dllexport)
		#else
			#define SATURN_API __declspec(dllimport)
		#endif
	#elif defined __GNUC__
		#define SATURN_API __attribute__((visibility("default")))
	#endif
#else
	#define SATURN_API
#endif
// End of DLL support

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

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
