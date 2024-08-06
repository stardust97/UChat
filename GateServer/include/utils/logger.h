#ifndef _UCHAT_GATE_SERVER_UTILS_LOGGER_H_
#define _UCHAT_GATE_SERVER_UTILS_LOGGER_H_

// todo optional
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
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
    KTrace = 0,
    kDebug = 1,
    kInfo = 2,
    kWarn = 3,
    kError = 4,
    kFatal = 5,
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
  void log_to_file(LogLevel level, const char *format, Args &&...args) {
    if (!file_logger_) {
      return;
    }
    switch (level) {
    case LogLevel::kFatal:
      file_logger_->critical(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kError:
      file_logger_->error(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kWarn:
      file_logger_->warn(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kInfo:
      file_logger_->info(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kDebug:
      file_logger_->debug(format, std::forward<Args>(args)...);
    case LogLevel::KTrace:
      file_logger_->trace(format, std::forward<Args>(args)...);
    default:
      break;
    }
  }

  template <typename... Args>
  void log_to_console(LogLevel level, const char *format, Args &&...args) {
    if (!console_logger_) {
      return;
    }
    switch (level) {
    case LogLevel::kFatal:
      console_logger_->critical(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kError:
      console_logger_->error(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kWarn:
      console_logger_->warn(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kInfo:
      console_logger_->info(format, std::forward<Args>(args)...);
      break;
    case LogLevel::kDebug:
      console_logger_->debug(format, std::forward<Args>(args)...);
    case LogLevel::KTrace:
      console_logger_->trace(format, std::forward<Args>(args)...);
    default:
      break;
    }
  }

  template <typename... Args>
  void Log(LogLevel level, const char *filename_in, int line_in,
           const char *funcname_in, const char* format, Args &&...args) {
    if (level_ > level) {
      return;
    }
    std::string message = std::string(filename_in) + ":" +
                          std::to_string(line_in) + " [" + funcname_in + "] " +
                          format;

    log_to_console(level, format, std::forward<Args>(args)...);
    log_to_file(level, message.c_str(), std::forward<Args>(args)...);
    if(level == LogLevel::kFatal){
      throw std::runtime_error("fatal error!");
    }
 }

  void SetLevel(LogLevel level);

  std::shared_ptr<spdlog::logger> GetConsoleLogger() { return console_logger_; }

  std::shared_ptr<spdlog::logger> GetFileLogger() { return file_logger_; }

private:
  Logger() = default;

private:
  std::shared_ptr<spdlog::logger> console_logger_;
  std::shared_ptr<spdlog::logger> file_logger_;
  LogLevel level_;
};
} // namespace uchat

#define LogTrace(format, ...)                                                  \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.Log(Logger::LogLevel::KTrace, __FILE__, __LINE__,                   \
               static_cast<const char *>(__FUNCTION__), format,                \
               ##__VA_ARGS__);                                                 \
  } while (0)

#define LogDebug(format, ...)                                                  \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.Log(Logger::LogLevel::kDebug, __FILE__, __LINE__,                   \
               static_cast<const char *>(__FUNCTION__), format,                \
               ##__VA_ARGS__);                                                 \
  } while (0)

#define LogInfo(format, ...)                                                   \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.Log(Logger::LogLevel::kInfo, __FILE__, __LINE__,                    \
               static_cast<const char *>(__FUNCTION__), format,                \
               ##__VA_ARGS__);                                                 \
  } while (0)

#define LogWarn(format, ...)                                                   \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.Log(Logger::LogLevel::kWarn, __FILE__, __LINE__,                    \
               static_cast<const char *>(__FUNCTION__), format,                \
               ##__VA_ARGS__);                                                 \
  } while (0)

#define LogError(format, ...)                                                  \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.Log(Logger::LogLevel::kError, __FILE__, __LINE__,                   \
               static_cast<const char *>(__FUNCTION__), format,                \
               ##__VA_ARGS__);                                                 \
  } while (0)

#define LogFatal(format, ...)                                                  \
  do {                                                                         \
    auto &logger = uchat::Logger::GetInstance();                               \
    logger.Log(Logger::LogLevel::kFatal, __FILE__, __LINE__,                   \
               static_cast<const char *>(__FUNCTION__), format,                \
               ##__VA_ARGS__);                                                 \
  } while (0)

#endif