#include "verify_grpc_client.h"

namespace uchat {
namespace gate_server {
VerifyGrpcClient::VerifyGrpcClient() {
  auto channel = grpc::CreateChannel("127.0.0.1:50051",
                                     grpc::InsecureChannelCredentials());
  stub_ = message::VerifyService::NewStub(channel);
}

message::GetVerifyRsp VerifyGrpcClient::GetVerifyCode(std::string_view email) {
  message::GetVerifyReq req;
  req.set_email(email.data());

  message::GetVerifyRsp rsp;
  grpc::ClientContext context;
  grpc::Status status = stub_->GetVerifyCode(&context, req, &rsp);
  if (status.ok()) {
    // rsp.set_error(Errorcode::)
  } else {
    // rsp.set_error(Errorcode::)
    LogError("get verfiy code error: {}", status.error_code());
  }
  return rsp;
}
}
}