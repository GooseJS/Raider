#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Raider/Core.h"

namespace Raider
{
	class RAIDER_API Logger
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return _coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return _clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> _coreLogger;
		static std::shared_ptr<spdlog::logger> _clientLogger;
	};
}

#define RD_CORE_TRACE(...)   ::Raider::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define RD_CORE_INFO(...)    ::Raider::Logger::getCoreLogger()->info(__VA_ARGS__)
#define RD_CORE_WARN(...)    ::Raider::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define RD_CORE_ERROR(...)   ::Raider::Logger::getCoreLogger()->error(__VA_ARGS__)
#define RD_CORE_CRITICAL(...)   ::Raider::Logger::getCoreLogger()->critical(__VA_ARGS__)

#define RD_TRACE(...)   ::Raider::Logger::getClientLogger()->trace(__VA_ARGS__)
#define RD_INFO(...)    ::Raider::Logger::getClientLogger()->info(__VA_ARGS__)
#define RD_WARN(...)    ::Raider::Logger::getClientLogger()->warn(__VA_ARGS__)
#define RD_ERROR(...)   ::Raider::Logger::getClientLogger()->error(__VA_ARGS__)
#define RD_CRITICAL(...)   ::Raider::Logger::getClientLogger()->critical(__VA_ARGS__)