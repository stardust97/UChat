#ifndef _UCHAT_GATE_SERVER_ACCEPTOR_H_
#define _UCHAT_GATE_SERVER_ACCEPTOR_H_

#include <memory>

#include "net_const.h"

namespace uchat {
namespace gate_server {
  
class BoostAcceptor : public std::enable_shared_from_this<BoostAcceptor>{
public:
  BoostAcceptor(uc_ion_contex& ioc,unsigned short port);
  ~BoostAcceptor();
  
  BoostAcceptor(BoostAcceptor const &) = delete;
  BoostAcceptor(BoostAcceptor &&) = delete;
  BoostAcceptor &operator=(BoostAcceptor const &) = delete;
  BoostAcceptor &operator=(BoostAcceptor &&) = delete;

  // start to accepter a new http connection
  void Start();

private:
  uc_ion_contex& ioc_;
  uctcp::acceptor acceptor_;
};

} // namespace gate_server
} //namespace uchat

#endif 