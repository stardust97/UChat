#include "rpc/verify_grpc_client.h"


using namespace uchat::gate_server;

int main() {
  auto &log = uchat::Logger::GetInstance();
  log.Init("conf/log_setting.json");
  VerifyGrpcClient& client = VerifyGrpcClient::GetInstance();

  message::GetVerifyRsp rsp = client.GetVerifyCode("2387069619@qq.com") ;

  std::cout << "get code:"<<rsp.code() << std::endl;
}