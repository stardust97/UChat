#include "boost_component/io_context_pool.h"

#include "utils/logger.h"
#include "common/server_setting.h"
namespace uchat {
namespace gate_server {
IoContextPool::IoContextPool()
    : io_contexts_{http_config::KIoThreadNum},
      works_{http_config::KIoThreadNum}, threads_{0}, accept_io_context_{},
      next_context_index_{0} {
  for (std::size_t i = 0; i < http_config::KIoThreadNum; ++i) {
    works_[i] = std::unique_ptr<Work>(new Work(io_contexts_[i]));
  }
  for (std::size_t i = 0; i < http_config::KIoThreadNum; ++i) {
    threads_.emplace_back([this, i] { io_contexts_[i].run(); });
  }
}
IoContextPool::~IoContextPool() {
  destroy();
  LogInfo("IoContextPool destroyed");
}
ucasio::io_context& IoContextPool::GetConnContext(){
  ucasio::io_context &cur_context = io_contexts_[next_context_index_++];
  if (next_context_index_ == io_contexts_.size()) {
    next_context_index_ = 0;
  }
  return cur_context;
}

ucasio::io_context &IoContextPool::GetAcceptContext() {
  return accept_io_context_;
}

void IoContextPool::destroy() {
  for(auto& work : works_){
    work->get_io_context().stop();
    work.reset();
  }
  for(auto& thread : threads_){
    thread.join();
  }
}

} // namespace gate_server
} // namespace uchat