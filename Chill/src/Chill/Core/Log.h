#pragma once

#include<memory>

#include "Chill/Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Chill 
{

	class Log
	{
	public:
		static void Initialize();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

#define CH_CORE_TRACE(...)::Chill::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CH_CORE_INFO(...)::Chill::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CH_CORE_WARN(...)::Chill::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CH_CORE_ERROR(...)::Chill::Log::GetCoreLogger()->error(__VA_ARGS__)


#define CH_TRACE(...)::Chill::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CH_INFO(...)::Chill::Log::GetClientLogger()->info(__VA_ARGS__)
#define CH_WARN(...)::Chill::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CH_ERROR(...)::Chill::Log::GetClientLogger()->error(__VA_ARGS__)

