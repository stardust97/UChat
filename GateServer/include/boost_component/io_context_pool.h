#ifndef _UCHAT_GATE_SERVER_IO_CONTEXT_POOL_H_
#define _UCHAT_GATE_SERVER_IO_CONTEXT_POOL_H_

#include "common/net_const.h"

namespace uchat {
namespace gate_server {
// use one accept context and multiple connection context
class IoContextPool{
public:
  static IoContextPool &GetInstance() {
    static IoContextPool instance;
    return instance;
  }

  ~IoContextPool();
  
  ucasio::io_context &GetConnContext();
  ucasio::io_context &GetAcceptContext();

private:
  IoContextPool();

  void destroy();

private:
  using IOService = boost::asio::io_context;
  using Work = boost::asio::io_context::work;
  using WorkPtr = std::unique_ptr<Work>;
  std::vector<IOService> io_contexts_;
  std::vector<WorkPtr> works_;
  std::vector<std::thread> threads_;
  IOService accept_io_context_;
  std::size_t next_context_index_;
};

} // namespace gate_server
} // namespace uchat
#endif