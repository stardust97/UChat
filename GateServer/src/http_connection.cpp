#include "http_connection.h"

#include <cctype>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include "boost/beast/http/field.hpp"
#include "boost/beast/http/status.hpp"
#include "boost/beast/http/write.hpp"
#include "boost/system/detail/error_code.hpp"
#include "logic_system.h"
#include "net_const.h"
#include "server_setting.h"

namespace uchat {
namespace gate_server {

HttpConnection::HttpConnection(uc_ion_contex &ioc)
    : socket_{ioc}, buffer_{8192}, deadline_{
                                       socket_.get_executor(),
                                       std::chrono::seconds{KHttpCloseTime}} {}
HttpConnection::~HttpConnection() {}

void HttpConnection::Start() {
  auto self = shared_from_this();
  std::cout << "start to read mesg from client" << std::endl;
  uchttp::async_read(socket_, buffer_, request_,
                     [self](uc_error_code ec, std::size_t bytes_transferred) {
                       if (ec) {
                         std::cout << "http read err: " << ec.what()
                                   << std::endl;
                         return;
                       }
                       std::cout << "recv message from client" << std::endl;
                       self->handle_req();
                       self->check_deadline();
                     });
}

void HttpConnection::PreParseGetParam() {
  auto parm_pos = request_.target().find("?");
  if (parm_pos == std::string::npos) {
    std::cout << "no params in url" << std::endl;
    return;
  }
  url_ = request_.target().substr(0, parm_pos);
  std::string url_param = request_.target().substr(parm_pos);
  std::string::size_type pos_and1 = url_param.find("?");
  std::string::size_type pos_and2 = url_param.find("&", pos_and1 + 1);
  while (pos_and1 != std::string::npos) {
    if (pos_and2 != std::string::npos) {
      std::string decode_url =
          url_decode(url_param.substr(pos_and1 + 1, pos_and2 - pos_and1 - 1));
      parse_param(decode_url);
      pos_and2 = pos_and1;
      pos_and1 = url_param.find("&", pos_and2 + 1);
    } else {
      std::string decode_url = url_decode(url_param.substr(pos_and1));
      parse_param(decode_url);
      pos_and2 = pos_and1;
    }
  }
}

void HttpConnection::handle_req() {
  response_.version(request_.version());
  response_.keep_alive(false);
  auto self = shared_from_this();
  if (request_.method() == uchttp::verb::get) {
    PreParseGetParam();
    for (const auto &[k, v] : url_params_) {
      std::cout << k << ": " << v << std::endl;
    }
    bool handle_success = LogicSystem::GetInstance().HandleGet(url_, self);
    if (!handle_success) {
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

  // todo post
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
    if (!ec) { // 如果ec为0，说明是计时器超时（详看async_wait说明）
      // Close socket to cancel any outstanding operation.
      self->socket_.close(ec);
      // log
    }
    // 如果ec不为0，是由于计时器调用了cancel(), 产生的错误，
    // 也就是计时器没有超时，不执行close
  });
}

void HttpConnection::parse_param(std::string const &param_str) {
  std::string::size_type pos = param_str.find('=');
  std::string key = url_decode(param_str.substr(0, pos));
  std::string value = url_decode(param_str.substr(pos + 1));
  url_params_[key] = value;
}

// 0~9 -> 0~9, 10 ~15 -> A~F
unsigned char HttpConnection::dec_to_hex(unsigned char c) {
  return c > 9 ? (c + 'A' - 10) : (c + '0');
}
// 0~9 -> 0~9, A~F -> 10 ~15
unsigned char HttpConnection::hex_to_dec(unsigned char c) {
  return c > 'A' ? (c - 'A' + 10) : (c - '0');
}

std::string HttpConnection::url_encode(const std::string &str) {
  std::string result;
  for (int i = 0; i < str.size(); i++) {
    if (std::isalnum(str[i]) || str[i] == '-' || str[i] == '_' ||
        str[i] == '.' || str[i] == '~') {
      result.push_back(str[i]);
    } else if (str[i] == ' ') {
      result += "+";
    } else {
      result += "%";
      result += dec_to_hex(static_cast<unsigned char>(str[i] >> 4));
      result += dec_to_hex(static_cast<unsigned char>(str[i] & 0x0F));
    }
  }
  return result;
}

std::string HttpConnection::url_decode(const std::string &str) {
  std::string result;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '+') {
      result += ' ';
    } else if (str[i] == '%') {
      if (i + 2 < str.size() && str[i + 1] == '2' && str[i + 2] == '0') {
        result += ' ';
        i += 2;
        continue;
      }
      i++;
      unsigned char num = 0;
      num += hex_to_dec(str[i]) << 4;
      i++;
      num += hex_to_dec(str[i]);
      result += num;
    } else {
      result += str[i];
    }
  }
  return result;
}

} // namespace gate_server
} // namespace uchat
