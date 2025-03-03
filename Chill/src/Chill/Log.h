#pragma once

#include<memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Chill 
{

	class CHILL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return s_CoreLogger;}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
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

