#pragma once

#include "Application.h"
#include "Log.h"

#ifdef ST_PLATFORM_WINDOWS

extern Saturn::Application* Saturn::CreateApplication();

int main(int argc, char** argv)
{
	Saturn::Log::Init();

	ST_PROFILE_BEGIN_SESSION("Startup", "startup.stprofile.json");
	auto app = Saturn::CreateApplication();
	ST_PROFILE_END_SESSION();
	
	ST_PROFILE_BEGIN_SESSION("Runtime", "runtime.stprofile.json");
	app->Run();
	ST_PROFILE_END_SESSION();
	
	delete app;
}

#endif

#ifdef ST_PLATFORM_LINUX

extern Saturn::Application* Saturn::CreateApplication();

int main(int argc, char* argv)
{
	Saturn::Log::Init();
	auto app = Saturn::CreateApplication();
	app->Run();
	delete app;
}

#endif
