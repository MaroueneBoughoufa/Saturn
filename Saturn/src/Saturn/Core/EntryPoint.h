#pragma once

#include "Application.h"
#include "Log.h"

extern Saturn::Application* Saturn::CreateApplication();

namespace Saturn
{
	int Main(int argc, char* argv[])
	{
		Saturn::Log::Init();

		ST_PROFILE_BEGIN_SESSION("Startup", "startup.stprofile.json");
		auto app = Saturn::CreateApplication();
		ST_PROFILE_END_SESSION();

		ST_PROFILE_BEGIN_SESSION("Runtime", "runtime.stprofile.json");
		app->Run();
		ST_PROFILE_END_SESSION();

		ST_PROFILE_BEGIN_SESSION("Shutdown", "shutdown.stprofile.json");
		delete app;
		ST_PROFILE_END_SESSION();

		return 0;
	}
}

#if defined(ST_PLATFORM_WINDOWS) && defined(ST_DIST)
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Saturn::Main(__argc, __argv);
}
#else
int main(int argc, char** argv)
{
	return Saturn::Main(argc, argv);
}
#endif
