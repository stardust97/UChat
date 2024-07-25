#include "utils/server_setting.h"
#include "utils/logger.h"

#include <fstream>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <stdexcept>

namespace uchat {
  namespace gate_server {

  namespace http_config {
   std::uint8_t KHttpCloseTime{60}; // seconds
   std::uint16_t KReadBufferSize{8192};
   } // namespace http_config

  ConfigParser::ConfigParser() {

  }

  void ConfigParser::ParseJson(std::string_view json_path){
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string err;
    std::ifstream fin(json_path.data());
    if (!Json::parseFromStream(builder, fin, &root, &err)) {
      throw std::runtime_error("parse json file " + err);
    }
    if (!root.isMember("http_settings")) {
      auto http = root["http"];
      LogWarn("http settig json has no settings");
      return;
    }

    http_config::KReadBufferSize = root["http_settings"]["read_buf_size"].asUInt();
    http_config::KHttpCloseTime = root["http_settings"]["conn_timeout_seconds"].asUInt();
    LogInfo(
        "read http settings from json, KHttpCloseTime: {}, KReadBufferSize:{}",
        http_config::KHttpCloseTime, http_config::KReadBufferSize);
  }

  } // namespace gate_server
  } // namespace uchat
