#ifndef _UCHAT_GATE_SERVER_LOGIC_SYSTEM_H_
#define _UCHAT_GATE_SERVER_LOGIC_SYSTEM_H_

#include "http_connection.h"

#include <functional>
#include <memory>
#include <unordered_map>

#include "net_const.h"
#include "macro.h"

namespace uchat {
namespace gate_server {
  
class HttpConnection;

using HttpHandler = std::function<void(std::shared_ptr<HttpConnection>)>;

class LogicSystem {
public:
  static LogicSystem &GetInstance();

  ~LogicSystem();

  UNCOPYABLE(LogicSystem);

  bool HandleGet(std::string const &path,
                 std::shared_ptr<HttpConnection> connection);
  // todo
  //  bool HandlePost(std::string const& path,
  //                  std::shared_ptr<HttpConnection> connection);

  // 注册url对应的handler
  void RegisterHandler(std::string const &url, HttpHandler handler);

private:
  LogicSystem();

private:
  // 记录客户端可以请求的资源URL及其handler
  std::unordered_map<std::string, HttpHandler> post_handlers_;
  std::unordered_map<std::string, HttpHandler> get_handlers_;
};

}  // namespace gate_server
}  // namespace uchat

#endif