#ifndef _UCHAT_GATE_SERVER_UTILS_LOGGER_H_
#define _UCHAT_GATE_SERVER_UTILS_LOGGER_H_

#include <memory>
#include <string_view>

#include "spdlog/sinks/basic_file_sink.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>


#define LogInfo(Message) spdlog::info(Message)

#define LogWarn(Message) spdlog::warn(Message)

#define LogError(Message) spdlog::error(Message)

// #define LogInfo(Logger, Message) spdlog::info(Message)

// #define LogWarn(Logger, Message) spdlog::warn(Message)

// #define LogError(Logger, Message) spdlog::error(Message)

namespace uchat {
class Logger {
public:
  ~Logger() =default;

  // get global default logger
  static Logger &GetLogger();

  void Init(std::string_view config_path);
private:
  Logger() = default;

private:
  std::shared_ptr<spdlog::logger> logger_;
  std::shared_ptr<spdlog::sinks::basic_file_sink_mt> file_sink_;
  std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink_;
};

} // namespace uchat

#endif
