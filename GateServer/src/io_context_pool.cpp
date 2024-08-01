#include "io_context_pool.h"

#include "utils/server_setting.h"
namespace uchat {
namespace gate_server {
IoContextPool::IoContextPool()
    : io_contexts_{http_config::KIoThreadNum},
      works_{http_config::KIoThreadNum}, threads_{0}, next_context_index_{0} {
  for (std::size_t i = 0; i < http_config::KIoThreadNum; ++i) {
    works_[i] = std::unique_ptr<Work>(new Work(io_contexts_[i]));
  }
  for (std::size_t i = 0; i < http_config::KIoThreadNum; ++i) {
    threads_.emplace_back([this, i] { io_contexts_[i].run(); });
  }
}

ucasio::io_context& IoContextPool::GetContext(){
  ucasio::io_context &cur_context = io_contexts_[next_context_index_++];
  if (next_context_index_ == io_contexts_.size()) {
    next_context_index_ = 0;
  }
  return cur_context;
}

} // namespace gate_server
} // namespace uchat