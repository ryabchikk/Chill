#include "chpch.h"
#include "Chill/Core/Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
namespace Chill {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("CHILL CORE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("CHILL APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}