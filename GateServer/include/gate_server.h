#ifndef _UCHAT_GATE_SERVER_GATE_SERVER_H_
#define _UCHAT_GATE_SERVER_GATE_SERVER_H_

#include <memory>
#include <string_view>

#include "acceptor.h"
#include "net_const.h"

namespace uchat {
namespace gate_server {
class GateServer {
public:
  static GateServer &GetInstance();
  ~GateServer() = default;
  void Init(std::string_view http_setting_json_path);
  void Start();
  void Stop();

private:
  GateServer();

private:
  uc_ion_contex ioc_;
  std::shared_ptr<uchat::gate_server::BoostAcceptor> acceptor_;
};

} // namespace gate_server
} // namespace uchat

#endif