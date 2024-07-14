#include "utils/logger.h"

#include "spdlog/sinks/basic_file_sink.h"
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

namespace uchat {
Logger &Logger::GetLogger() {
  static Logger instance;
  return instance;
}

void Logger::Init(std::string_view config_path) {
  bool enable_console = false;
  // logger_ = spdlog::basic_logger_mt("file", "my_log.log");
  console_sink_ = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink_->set_level(spdlog::level::info);
  console_sink_->set_pattern("[console] [%^%l%$] %v");

  file_sink_ = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      "logs/multisink.txt", true);
  file_sink_->set_level(spdlog::level::trace);
  file_sink_->set_pattern("[file] [%^%l%$] %v");

  spdlog::sinks_init_list sink_list = {console_sink_, file_sink_};
  logger_ = std::make_shared<spdlog::logger>("multi_logger", sink_list.begin(),
                                             sink_list.end());

  spdlog::register_logger(logger_);
  logger_->set_level(spdlog::level::trace);
  logger_->flush_on(spdlog::level::trace);
}



} // namespace uchat