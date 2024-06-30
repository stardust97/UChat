#include "http_connection.h"

#include <cstdint>
#include <iostream>
#include <memory>

#include "logic_system.h"
#include "net_const.h"
#include "server_setting.h"
#include "boost/beast/http/field.hpp"
#include "boost/beast/http/status.hpp"
#include "boost/beast/http/write.hpp"
#include "boost/system/detail/error_code.hpp"


namespace uchat {
namespace gate_server {

HttpConnection::HttpConnection(uc_ion_contex &ioc)
    : socket_{ioc}, buffer_{8192}, deadline_{
                                       socket_.get_executor(),
                                       std::chrono::seconds{KHttpCloseTime}} {}
HttpConnection::~HttpConnection(){}

void HttpConnection::Start() {
  auto self = shared_from_this();
  uchttp::async_read(
      socket_, buffer_, request_,
      [self](uc_error_code ec, std::size_t bytes_transferred) {
        if (ec) {
          std::cout << "http read err: " << ec.what() << std::endl;
          return;
        }
        self->handle_req();
        self->check_deadline();
      });
}

void HttpConnection::handle_req() {
  //设置版本
  response_.version(request_.version());
  //设置为短链接
  response_.keep_alive(false);
  auto self = shared_from_this();
  if(request_.method() == uchttp::verb::get) {
    bool handle_success =
        LogicSystem::GetInstance().HandleGet(request_.target(), self);
    if(!handle_success) {
      response_.result(uchttp::status::not_found);
      response_.set(uchttp::field::content_type, "text/plain");
      write_response();
      return;
    }

    response_.result(uchttp::status::ok);
    response_.set(uchttp::field::server, "GateServer");
    write_response();
    return;
  }

  //todo post


}

void HttpConnection::write_response() {
  auto self = shared_from_this();
  uchttp::async_write(
      socket_, response_, [self](boost::system::error_code ec, std::size_t) {
        self->socket_.shutdown(uctcp::socket::shutdown_type::shutdown_send, ec);
        self->deadline_.cancel(); // 取消执行等待此计时器的异步操作
      });
}

void HttpConnection::check_deadline() {
  auto self = shared_from_this();
  deadline_.async_wait([self](uc_error_code ec) {
    if(!ec) { // 如果ec为0，说明是计时器超时（详看async_wait说明）
      // Close socket to cancel any outstanding operation.
      self->socket_.close(ec);
      // log
    }
    // 如果ec不为0，是由于计时器调用了cancel(), 产生的错误，
    // 也就是计时器没有超时，不执行close
  });
}

} // namespace gate_server
} //namespace uchat


