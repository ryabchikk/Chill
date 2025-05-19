#pragma once

#include <memory>

#ifdef _WIN32
#ifdef _WIN64
#define CH_PLATFORM_WINDOWS
#else
#error "x86 Builds are not supported!"
#endif
#else
#error "Unknown platform!"
#endif

#ifdef CH_DEBUG
#define CH_ENABLE_ASSERTS
#endif

#ifdef CH_ENABLE_ASSERTS
#define CH_ASSERT(x, ...) { if(!(x)) { CH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define CH_CORE_ASSERT(x, ...) { if(!(x)) { CH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define CH_ASSERT(x, ...)
#define CH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Chill 
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