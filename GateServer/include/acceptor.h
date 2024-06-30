#ifndef _UCHAT_GATE_SERVER_ACCEPTOR_H_
#define _UCHAT_GATE_SERVER_ACCEPTOR_H_

#include <memory>

#include "net_const.h"

namespace uchat {
namespace gate_server {
  
class Accptor : public std::enable_shared_from_this<Accptor>{
public:
  Accptor(uc_ion_contex& ioc,unsigned short port);
  ~Accptor();
  
  Accptor(Accptor const &) = delete;
  Accptor(Accptor &&) = delete;
  Accptor &operator=(Accptor const &) = delete;
  Accptor &operator=(Accptor &&) = delete;

  // start to accepter a new http connection
  void Start();

private:
  uc_ion_contex& ioc_;
  uctcp::acceptor acceptor_;
};

} // namespace gate_server
} //namespace uchat

#endif 