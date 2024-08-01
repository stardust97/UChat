#ifndef _UCHAT_GATE_SERVER_IO_CONTEXT_POOL_H_
#define _UCHAT_GATE_SERVER_IO_CONTEXT_POOL_H_

#include "net_const.h"

namespace uchat {
namespace gate_server {
class IoContextPool{

public:
static IoContextPool& GetInstance(){
  static IoContextPool instance;
  return instance;
}

ucasio::io_context& GetContext();

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
  std::size_t next_context_index_;

};

} // namespace gate_server
} // namespace uchat
#endif