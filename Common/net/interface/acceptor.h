#ifndef _UCHAT_NET_ACCEPTOR_H_
#define _UCHAT_NET_ACCEPTOR_H_

#include <functional>
#include <memory>

namespace uchat {
class Connection;
class Accptor : public std::enable_shared_from_this<Accptor> {
public:
  using ConnectionCallback = std::function<void(void)>;

  Accptor() = default;

  virtual~Accptor();

  // start to accepter a new connection
  virtual void Start() = 0;

  virtual void SetNewConnectionCallback(ConnectionCallback &&cb) = 0;
};

} // namespace uchat

#endif