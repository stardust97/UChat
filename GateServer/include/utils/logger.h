#ifndef _UCHAT_GATE_SERVER_UTILS_LOGGER_H_
#define _UCHAT_GATE_SERVER_UTILS_LOGGER_H_

#include <memory>
#include <string_view>

#include "spdlog/sinks/basic_file_sink.h"
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

// #define LogInfo(Logger, Message) spdlog::info(Message)

// #define LogWarn(Logger, Message) spdlog::warn(Message)

// #define LogError(Logger, Message) spdlog::error(Message)

namespace uchat {
class Logger {
public:
  enum class LogLevel : std::uint8_t {
    kDebug = 0,
    kInfo = 1,
    kWarn = 2,
    kError = 3,
    kFatal = 4,
  };

  ~Logger() = default;
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;
  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;

  // get global default logger
  static Logger &GetInstance();

  void Init(std::string_view config_path);

  void LogFile(std::string_view message, LogLevel level);

  void LogConsole(std::string_view message, LogLevel level);

  void SetLevel(LogLevel level);

private:
  Logger() = default;

private:
  std::shared_ptr<spdlog::logger> console_logger_;
  std::shared_ptr<spdlog::logger> file_logger_;
  LogLevel level_;
};
} // namespace uchat

#define LogInfo(Message)                                                       \
  do {                                                                         \
    auto& logger = uchat::Logger::GetInstance();                                \
    logger.LogFile(Message, Logger::LogLevel::kInfo);                          \
    logger.LogConsole(Message, Logger::LogLevel::kInfo);                       \
  } while (0)

#define LogWarn(Message)                                                       \
  do {                                                                         \
    auto logger = uchat::Logger::GetInstance();                                \
    logger.LogFile(Message, Logger::LogLevel::kWarn);                          \
    logger.LogConsole(Message, Logger::LogLevel::kWarn);                       \
  } while (0)

#define LogError(Message)                                                      \
  do {                                                                         \
    auto& logger = uchat::Logger::GetInstance();                                \
    logger.LogFile(Message, Logger::LogLevel::kError);                         \
    logger.LogConsole(Message, Logger::LogLevel::kError);                      \
  } while (0)

#endif