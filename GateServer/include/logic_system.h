#ifndef _UCHAT_GATE_SERVER_LOGIC_SYSTEM_H_
#define _UCHAT_GATE_SERVER_LOGIC_SYSTEM_H_

#include <functional>
#include <memory>
#include <unordered_map>
#include <string>

#include "common/macro.h"

namespace uchat {
namespace gate_server {
  
class HttpConnection;

using HttpHandler = std::function<void(std::shared_ptr<HttpConnection>)>;

class LogicSystem {
public:
  static LogicSystem &GetInstance();

  ~LogicSystem() = default;

  UNCOPYABLE(LogicSystem);

  bool HandleGet(std::string const &path,
                 std::shared_ptr<HttpConnection> connection);

  bool HandlePost(std::string const &path,
                  std::shared_ptr<HttpConnection> connection);

private:
  LogicSystem();

  void registe_get_handler(std::string const &url, HttpHandler handler);
  void registe_post_handler(std::string const &url, HttpHandler handler);

  void on_recv_test_req(HttpConnection* conn);
  void on_recv_regist_req(HttpConnection* conn);

private:
  std::unordered_map<std::string, HttpHandler> post_handlers_;
  std::unordered_map<std::string, HttpHandler> get_handlers_;
};

}  // namespace gate_server
}  // namespace uchat

#endif