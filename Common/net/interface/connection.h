#ifndef _UCHAT_NET_CONNECTION_H_
#define _UCHAT_NET_CONNECTION_H_

#include <functional>
#include <memory>

namespace uchat {
class Connection : public std::enable_shared_from_this<Connection> {
public:
  using MessageCallback = std::function<void(void)>;
  Connection() = default;
  virtual ~Connection() = default;

  virtual void Start() = 0;
  virtual void SetNewMessageCallback(MessageCallback &&cb) = 0;
};

} // namespace uchat

#endif