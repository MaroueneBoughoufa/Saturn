#pragma once

#include "retropch.h"

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Retro
{
	class RETRO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Logger macros
#define Rtro_CORE_TRACE(...)     Retro::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define Rtro_CORE_INFO(...)      Retro::Log::GetCoreLogger()->info(__VA_ARGS__)
#define Rtro_CORE_WARN(...)      Retro::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define Rtro_CORE_ERROR(...)     Retro::Log::GetCoreLogger()->error(__VA_ARGS__)
#define Rtro_CORE_FATAL(...)     Retro::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Logger macros
#define Rtro_TRACE(...)          Retro::Log::GetClientLogger()->trace(__VA_ARGS__)
#define Rtro_INFO(...)           Retro::Log::GetClientLogger()->info(__VA_ARGS__)
#define Rtro_WARN(...)           Retro::Log::GetClientLogger()->warn(__VA_ARGS__)
#define Rtro_ERROR(...)          Retro::Log::GetClientLogger()->error(__VA_ARGS__)
#define Rtro_FATAL(...)          Retro::Log::GetClientLogger()->fatal(__VA_ARGS__)