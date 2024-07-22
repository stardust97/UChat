#include "acceptor.h"

#include <iostream>
#include <memory>

#include "boost/system/detail/error_code.hpp"
#include "http_connection.h"
#include "net_const.h"

namespace uchat {
namespace gate_server {

BoostAcceptor::BoostAcceptor(uc_ion_contex &ioc, std::string const &ip,
                             unsigned short port)
    : ioc_{ioc}, acceptor_{ioc_, {ucasio::ip::make_address(ip), port}} {}

BoostAcceptor::~BoostAcceptor() {}

void BoostAcceptor::Start() {
  auto self = shared_from_this();
  std::shared_ptr<HttpConnection> conn = std::make_shared<HttpConnection>(ioc_);
  // uctcp::socket socket;
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
