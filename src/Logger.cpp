//
// Created by ikmokhirio on 26.06.2022.
//

#include "Logger.h"

namespace Daedalus {

    std::shared_ptr<spdlog::logger> Logger::coreLogger;
    std::shared_ptr<spdlog::logger> Logger::applicationLogger;

    void Logger::InitLogger() {
        // Init logger
        spdlog::set_pattern("%^[%T] %n: %v%$");

        coreLogger = spdlog::stdout_color_mt("DAEDALUS");
        coreLogger->set_level(spdlog::level::trace);

        applicationLogger = spdlog::stdout_color_mt("APP");
        applicationLogger->set_level(spdlog::level::trace);
    }
}