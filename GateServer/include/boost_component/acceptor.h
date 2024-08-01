#ifndef _UCHAT_GATE_SERVER_ACCEPTOR_H_
#define _UCHAT_GATE_SERVER_ACCEPTOR_H_

#include <functional>
#include <memory>

#include "common/macro.h"
#include "common/net_const.h"

namespace uchat {
namespace gate_server {
  
class BoostAcceptor : public std::enable_shared_from_this<BoostAcceptor>{
public:
  using NewConnCb = std::function<void(std::shared_ptr<uctcp::socket>)>;

  BoostAcceptor(uc_ion_contex& ioc,std::string const& ip, unsigned short port);
  ~BoostAcceptor() = default;

  UNCOPYABLE(BoostAcceptor);

  void SetConnectionCb(NewConnCb cb) { cb_ = cb; }
  // start to accepter a new http connection
  void Start();

private:
  uc_ion_contex& ioc_;
  uctcp::acceptor acceptor_;
  NewConnCb cb_;
};

} // namespace gate_server
} //namespace uchat

#endif 