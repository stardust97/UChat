#include "gate_server.h"
#include "utils/logger.h"

int main() {
  auto &log = uchat::Logger::GetInstance();
  log.Init("conf/log_setting.json");
  auto &server = uchat::gate_server::GateServer::GetInstance();
  server.Init("conf/http_setting.json");
  server.Start();

  return 0;
}