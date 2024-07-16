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

  template <typename... Args>
  void LogFile(LogLevel level, const char *format, Args &&... args) {
    if (level_ > level || !file_logger_) {
      return;
    }
    switch (level) {
    case LogLevel::kError:
      file_logger_->error(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kWarn:
      file_logger_->warn(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kInfo:
      file_logger_->info(format, std::forward<Args>(args)...);
      break;
    default:
      file_logger_->trace(format, std::forward<Args>(args)...);
      break;
    }
  }

  template <typename... Args>
  void LogConsole(LogLevel level, const char *format, Args &&... args) {
    if (level_ > level || !console_logger_) {
      return;
    }
    switch (level) {
    case LogLevel::kError:
      console_logger_->error(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kWarn:
      console_logger_->warn(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kInfo:
      console_logger_->info(format, std::forward<Args>(args)...);
      break;
    default:
      console_logger_->trace(format, std::forward<Args>(args)...);
      break;
    }
  }

  void SetLevel(LogLevel level);

private:
  Logger() = default;

private:
  std::shared_ptr<spdlog::logger> console_logger_;
  std::shared_ptr<spdlog::logger> file_logger_;
  LogLevel level_;
};
} // namespace uchat

#define LogInfo(format, ...)                                                   \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.LogFile(Logger::LogLevel::kInfo, format, ##__VA_ARGS__);            \
    logger.LogConsole(Logger::LogLevel::kInfo, format, ##__VA_ARGS__);          \
  } while (0)

#define LogWarn(format, ...)                                                   \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.LogFile(Logger::LogLevel::kWarn, format, ##__VA_ARGS__);            \
    logger.LogConsole(Logger::LogLevel::kWarn, format, ##__VA_ARGS__);          \
  } while (0)

#define LogError(format, ...)                                                  \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.LogFile(Logger::LogLevel::kError, format, ##__VA_ARGS__);           \
    logger.LogConsole(Logger::LogLevel::kError, format, ##__VA_ARGS__);         \
  } while (0)

#endif