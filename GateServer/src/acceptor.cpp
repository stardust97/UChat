#include "acceptor.h"

#include <iostream>
#include <memory>
#include <utility>

#include "boost/system/detail/error_code.hpp"
#include "http_connection.h"
#include "net_const.h"
#include "utils/logger.h"

namespace uchat {
namespace gate_server {

BoostAcceptor::BoostAcceptor(uc_ion_contex &ioc, std::string const &ip,
                             unsigned short port)
    : ioc_{ioc}, acceptor_{ioc_, {ucasio::ip::make_address(ip), port}} {}

void BoostAcceptor::Start() {
  auto self = shared_from_this();
  std::shared_ptr<uctcp::socket> socket = std::make_shared<uctcp::socket>(ioc_);
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
