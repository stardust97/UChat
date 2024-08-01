#ifndef _UCHAT_COMMON_SERVER_CONFIG_PARSER_H_
#define _UCHAT_COMMON_SERVER_CONFIG_PARSER_H_

#include <string_view>

namespace uchat {
namespace gate_server {
namespace http_config {
extern std::uint8_t KHttpCloseTime;
extern std::uint16_t KReadBufferSize;
extern std::uint16_t KIoThreadNum;
} // namespace http_config

class ConfigParser {
public:
  ConfigParser() = default;
  ~ConfigParser() = default;
  
  void ParseJson(std::string_view json_path);
private:
};
} // namespace gate_server
} // namespace uchat
#endif
