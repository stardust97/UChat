#include "gate_server.h"

#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <scoped_allocator>
#include <stdexcept>
#include <string>
#include <utility>

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "http_connection.h"
#include "utils/logger.h"

namespace uchat {
namespace gate_server {
GateServer::GateServer() : ioc_{1}, acceptor_{nullptr} {}

GateServer &GateServer::GetInstance() {
  static GateServer instance;
  return instance;
}

void GateServer::Init(std::string_view http_setting_json_path) {
  Json::Value root;
  Json::CharReaderBuilder builder;
  std::ifstream fin(http_setting_json_path.data());
  std::string err;
  if(!Json::parseFromStream(builder, fin, &root, &err)){
    LogError("parse http setting json path failed: {}", err);
    throw std::runtime_error("parse http setting json path failed" + err);
  }
  std::string ip_addr = root["ip_addr"].asString();
  std::uint16_t port = root["port"].asUInt();
  std::uint16_t conn_timeout_ms = root["conn_timeout_ms"].asUInt();
  
  acceptor_ =
      std::make_shared<uchat::gate_server::BoostAcceptor>(ioc_, ip_addr, port);
  acceptor_->SetConnectionCb(
      std::bind(&GateServer::on_new_conn, this, std::placeholders::_1));
  LogInfo("init acceptor, ip: {}, port: {}", ip_addr, port);
}

void GateServer::Start() {
  boost::asio::signal_set signals(ioc_, SIGINT, SIGTERM);
  signals.async_wait(
      [this](const boost::system::error_code &error, int signal_number) {
        if (error) {
          return;
        }
        this->Stop();
      });
  acceptor_->Start();
  std::cout << "start gete server" << std::endl;
  LogInfo("start gete server");
  ioc_.run();
}

void GateServer::Stop() { ioc_.stop(); }

void GateServer::on_new_conn(std::shared_ptr<uctcp::socket> socket) {
  auto conn =std::make_shared<HttpConnection>(socket);
  conn->Start();
}

} // namespace gate_server
} // namespace uchat
