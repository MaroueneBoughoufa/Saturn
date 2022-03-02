#pragma once

#include "Application.h"
#include "Log.h"

#ifdef Rtro_PLATFORM_WINDOWS

extern Retro::Application* Retro::CreateApplication();

int main(int argc, char** argv[])
{
	Retro::Log::Init();
	Rtro_CORE_WARN("Initiallized Logg.");
	Rtro_INFO("Hello! Welcome to the <Retro Engine> !");

	auto app = Retro::CreateApplication();
	app->Run();
	delete app;
}

#endif

#ifdef Rtro_PLATFORM_LINUX

extern Retro::Application* Retro::CreateApplication();

int main(int argc, char* argv[])
{
	Retro::Log::Init();
	Rtro_CORE_WARN("Initiallized Logg.");
	Rtro_INFO("Hello! Welcome to the <Retro Engine> !");

	auto app = Retro::CreateApplication();
	app->Run();
	delete app;
}

#endif