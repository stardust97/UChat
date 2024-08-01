#include "common/server_setting.h"

#include <fstream>
#include <stdexcept>

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "utils/logger.h"


namespace uchat {
namespace gate_server {
namespace http_config {
  std::uint8_t KHttpCloseTime{60}; // seconds
  std::uint16_t KReadBufferSize{8192};
  std::uint16_t KIoThreadNum{2};
} // namespace http_config
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
    http_config::KIoThreadNum = root["io_thread_num"].asUInt();
    LogInfo("read http settings from json, KHttpCloseTime: {}, "
            "KReadBufferSize:{}, KIoThreadNum: {}",
            http_config::KHttpCloseTime, http_config::KReadBufferSize,
            http_config::KIoThreadNum);
  }

} // namespace gate_server
} // namespace uchat
