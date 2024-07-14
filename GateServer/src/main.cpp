#include "gate_server.h"

int main() {
  auto& server = uchat::gate_server::GateServer::GetInstance();
  server.Init("");
  server.Start();

  return 0;
}