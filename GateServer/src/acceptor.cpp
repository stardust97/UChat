#include "acceptor.h"

#include <iostream>
#include <memory>

#include "boost/system/detail/error_code.hpp"
#include "http_connection.h"

namespace uchat {
namespace gate_server {

Accptor::Accptor(uc_ion_contex &ioc, unsigned short port)
    : ioc_{ioc}, acceptor_{ioc_, uctcp::endpoint(uctcp::v4(), port)} {}

Accptor::~Accptor() {}

void Accptor::Start() {
  auto self = shared_from_this();
  std::shared_ptr<HttpConnection> conn = std::make_shared<HttpConnection>(ioc_);
  acceptor_.async_accept(conn->GetSocket(),[self,conn](boost::system::error_code ec) {
    if (ec) {
      std::cout << "accept error: " << ec.message() << std::endl;
    } else {
      std::cout << "accept one connection" << std::endl;
      conn->Start();
    }
    self->Start();
  });
}

} // namespace gate_server
} // namespace uchat
