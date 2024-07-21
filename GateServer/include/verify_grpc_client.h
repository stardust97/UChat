#ifndef _UCHAT_GATE_SERVER_VERIFY_GRPC_CLIENT_H_
#define _UCHAT_GATE_SERVER_VERIFY_GRPC_CLIENT_H_

#include <memory>
#include <string_view>

#include "grpcpp/impl/codegen/status.h"
#include "macro.h"
#include "message.grpc.pb.h"
#include "message.pb.h"
#include "net_const.h"
#include "utils/logger.h"
#include <grpcpp/grpcpp.h>

namespace uchat {
namespace gate_server {

class VerifyClient {

public:
  VerifyClient& GetInstance() {
    static VerifyClient instance;
    return instance;
  }
  
  ~VerifyClient() = default;
  UNCOPYABLE(VerifyClient);

  message::GetVerifyRsp GetVarifyCode(std::string_view email) ;

private:
  VerifyClient();
private:
  std::unique_ptr<message::VerifyService::Stub> stub_;
};
} // namespace gate_server
} // namespace uchat
#endif
