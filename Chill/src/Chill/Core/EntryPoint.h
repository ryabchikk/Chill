#pragma once
#include "Chill/Core/Core.h"

#ifdef CH_PLATFORM_WINDOWS

extern Chill::Application* Chill::CreateApplication();

int main(int argc, char** argv)
{
	Chill::Log::Initialize();
	CH_PROFILE_BEGIN_SESSION("Startup", "chill_test_start.json");
	
	auto app = Chill::CreateApplication();
	
	CH_PROFILE_END_SESSION();

	CH_PROFILE_BEGIN_SESSION("Runtime", "chill_test_runtime.json");

	app->Run();

	CH_PROFILE_END_SESSION();

	CH_PROFILE_BEGIN_SESSION("Startup", "chill_test_end.json");
	
	delete app;
	
	CH_PROFILE_END_SESSION();
}

#endif
