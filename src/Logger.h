//
// Created by ikmokhirio on 26.06.2022.
//

#ifndef DAEDALUS_LOGGER_H
#define DAEDALUS_LOGGER_H

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Daedalus {
    class DAEDALUS_API Logger {
    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> applicationLogger;
    public:

        static void InitLogger();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return coreLogger; };

        inline static std::shared_ptr<spdlog::logger> &GetApplicationLogger() { return applicationLogger; };
    };
}

// Core logger
#define DS_CORE_TRACE(...) Daedalus::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define DS_CORE_WARN(...) Daedalus::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define DS_CORE_INFO(...) Daedalus::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define DS_CORE_ERROR(...) Daedalus::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define DS_CORE_FATAL(...) Daedalus::Logger::GetCoreLogger()->fatal(__VA_ARGS__)

// App logger
#define DS_TRACE(...) Daedalus::Logger::GetApplicationLogger()->trace(__VA_ARGS__)
#define DS_WARN(...) Daedalus::Logger::GetApplicationLogger()->warn(__VA_ARGS__)
#define DS_INFO(...) Daedalus::Logger::GetApplicationLogger()->info(__VA_ARGS__)
#define DS_ERROR(...) Daedalus::Logger::GetApplicationLogger()->error(__VA_ARGS__)
#define DS_FATAL(...) Daedalus::Logger::GetApplicationLogger()->fatal(__VA_ARGS__)

#endif //DAEDALUS_LOGGER_H
