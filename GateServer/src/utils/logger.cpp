#include "utils/logger.h"

#include <chrono>
#include <fstream>
#include <iostream>

#include "jsoncpp/json/json.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <system_error>

namespace uchat {
Logger &Logger::GetInstance() {
  static Logger instance;
  return instance;
}

void Logger::Init(std::string_view config_path) {
  std::fstream fin(config_path.data(), std::ios::in);
  if (!fin.is_open()) {
    throw std::runtime_error("Failed to open config file");
  }
  Json::Value root;
  Json::CharReaderBuilder builder;
  std::string err;
  if (!Json::parseFromStream(builder, fin, &root, &err)) {
    throw std::runtime_error("read param from file failed: " + err);
    return;
  }

  bool enable_console = root["enable_console"].asBool();
  bool enable_file = root["enable_file"].asBool();
  std::string level_str = root["log_level"].asString();
  if (level_str == "debug") {
    level_ = LogLevel::kDebug;
  } else if (level_str == "info") {
    level_ = LogLevel::kInfo;
  } else if (level_str == "warn") {
    level_ = LogLevel::kWarn;
  } else if (level_str == "error") {
    level_ = LogLevel::kError;
  } else {
    throw std::runtime_error("invalid log level: " + level_str);
    return;
  }

  std::string log_path = root["log_path"].asString();

  if (enable_console) {
    console_logger_ = spdlog::stdout_color_mt("defalut_console_logger");
    console_logger_->set_level(spdlog::level::info);
    console_logger_->set_pattern("[console] [%^%l%$] %v");
  }

  if (enable_file) {
    file_logger_ = spdlog::basic_logger_mt("default_file_logger", log_path);
    file_logger_->set_level(spdlog::level::info);
    file_logger_->set_pattern("[file] [%^%l%$] %v");
    file_logger_->info("File Logger Init succeed");
    spdlog::flush_every(std::chrono::seconds(1));
  }

  // logger_->flush_on(spdlog::level::trace);
}
void Logger::SetLevel(LogLevel level) { level_ = level; }


} // namespace uchat