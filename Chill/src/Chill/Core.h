#pragma once

#ifdef CH_PLATFORM_WINDOWS
	#ifdef CH_BUILD_DLL
		#define CHILL_API __declspec(dllexport)
	#else
		#define CHILL_API __declspec(dllexport)
	#endif
#else
	#error only support windows
#endif
