#ifndef _UCHAT_GATE_SERVER_HTTP_CONNECTION_H_
#define _UCHAT_GATE_SERVER_HTTP_CONNECTION_H_

#include <memory>

#include "logic_system.h"
#include "net_const.h"

namespace uchat {
namespace gate_server {

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
public:
  friend class LogicSystem;
  
  HttpConnection(uc_ion_contex& ioc);
  ~HttpConnection();

  // start to recv and handle a http message, no-blocked 
  void Start();

  uctcp::socket &GetSocket() { return socket_; }

  void PreParseGetParam();

#ifdef ENABLE_TEST
public:
#else
private:
#endif

  void handle_req();

  void write_response();

  void check_deadline();
  
  void parse_param(std::string const& param_str);

  unsigned char dec_to_hex(unsigned char c);
  unsigned char hex_to_dec(unsigned char c);

  std::string url_encode(const std::string &str);

  std::string url_decode(const std::string &str);

  uctcp::socket socket_;
  ucbeast::flat_buffer buffer_;
  ucbeast::net::steady_timer deadline_;
  uchttp::request<uchttp::dynamic_body> request_;
  uchttp::response<uchttp::dynamic_body> response_;
  std::string url_;
  std::unordered_map<std::string, std::string> url_params_;
};

} // namespace gate_server
} //namespace uchat


#endif