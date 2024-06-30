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

  // start to recv and handle a http message
  // no-blocked 
  void Start();

  uctcp::socket &GetSocket() { return socket_; }

private:

  void handle_req();

  void write_response();

  void check_deadline();

private:
  uctcp::socket socket_;
  ucbeast::flat_buffer buffer_;
  ucbeast::net::steady_timer deadline_;
  uchttp::request<uchttp::dynamic_body> request_;
  uchttp::response<uchttp::dynamic_body> response_;

};

} // namespace gate_server
} //namespace uchat


#endif