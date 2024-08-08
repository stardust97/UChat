#include "rpc/verify_grpc_client.h"
#include "common/server_setting.h"
#include "message.pb.h"

namespace uchat {
namespace gate_server {
VerifyGrpcClient::VerifyGrpcClient() {
  auto channel = grpc::CreateChannel(rpc_config::KVerifyServerAddr,
                                     grpc::InsecureChannelCredentials());
  stub_ = message::VerifyService::NewStub(channel);
}

message::GetVerifyRsp VerifyGrpcClient::GetVerifyCode(std::string_view email) {
  message::GetVerifyReq req;
  req.set_email(email.data());

  message::GetVerifyRsp rsp;
  grpc::ClientContext context;
  //todo timeout?
  grpc::Status status = stub_->GetVerifyCode(&context, req, &rsp);
  if (status.ok()) {
    rsp.set_error_code(message::ErrorCode::Succeed);
  } else {
    rsp.set_error_code(message::ErrorCode::Error);
    LogError("get verfiy code error: {}", status.error_code());
  }
  return rsp;
}
}
}