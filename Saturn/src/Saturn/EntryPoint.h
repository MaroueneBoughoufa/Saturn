#pragma once

#include "Application.h"
#include "Log.h"

#ifdef ST_PLATFORM_WINDOWS

extern Saturn::Application* Saturn::CreateApplication();

int main(int argc, char** argv[])
{
	Saturn::Log::Init();
	ST_CORE_WARN("Initiallized Logg.");
	ST_INFO("Hello! Welcome to the <Saturn Engine> !");

	auto app = Saturn::CreateApplication();
	app->Run();
	delete app;
}

#endif

#ifdef ST_PLATFORM_LINUX

extern Saturn::Application* Saturn::CreateApplication();

int main(int argc, char* argv[])
{
	Saturn::Log::Init();
	ST_CORE_WARN("Initiallized Logg.");
	ST_INFO("Hello! Welcome to the <Saturn Engine> !");

	auto app = Saturn::CreateApplication();
	app->Run();
	delete app;
}

#endif