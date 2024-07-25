#include <iostream>

#include "gate_server.h"
#include "utils/logger.h"

int main() {
  try{
  auto &log = uchat::Logger::GetInstance();
  log.Init("conf/log_setting.json");
  auto &server = uchat::gate_server::GateServer::GetInstance();
  server.Init("conf/gate_server_setting.json");
  server.Start();
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what();
  }

  return 0;
}