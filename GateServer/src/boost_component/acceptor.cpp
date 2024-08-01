#include "boost_component/acceptor.h"

#include <iostream>
#include <memory>
#include <utility>

#include "boost/system/detail/error_code.hpp"
#include "boost_component/http_connection.h"
#include "boost_component/io_context_pool.h"
#include "common/net_const.h"
#include "utils/logger.h"

namespace uchat {
namespace gate_server {

BoostAcceptor::BoostAcceptor(uc_ion_contex &ioc, std::string const &ip,
                             unsigned short port)
    : ioc_{ioc}, acceptor_{ioc_, {ucasio::ip::make_address(ip), port}} {}

void BoostAcceptor::Start() {
  auto self = shared_from_this();
  auto& context_ = IoContextPool::GetInstance().GetConnContext();
  std::shared_ptr<uctcp::socket> socket = std::make_shared<uctcp::socket>(context_);
  acceptor_.async_accept(
      *socket, [self, socket](boost::system::error_code ec) mutable {
        if (ec) {
          LogError("accept error: {}", ec.value());
        } else {
          self->cb_(socket);
        }
        self->Start();
      });
}

} // namespace gate_server
} // namespace uchat
