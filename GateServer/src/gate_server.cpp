#include "gate_server.h"
#include "utils/logger.h"

namespace uchat {
namespace gate_server {
GateServer::GateServer() : ioc_{1}, acceptor_{nullptr} {}

GateServer &GateServer::GetInstance() {
  static GateServer instance;
  return instance;
}

void GateServer::Init(std::string_view path) {
  // todo read json config file
  acceptor_ = std::make_shared<uchat::gate_server::BoostAcceptor>(ioc_, 8889);
  auto log = Logger::GetLogger();
  log.Init("");
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
  ioc_.run();
}

void GateServer::Stop() { ioc_.stop(); }

} // namespace gate_server
} // namespace uchat
