#include "logic_system.h"

#include <iostream>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <utility>

#include "boost/beast/core/ostream.hpp"
#include "boost_component/http_connection.h"
#include "common/net_const.h"
#include "utils/logger.h"
#include "rpc/verify_grpc_client.h"


namespace uchat {
namespace gate_server {

LogicSystem& LogicSystem::GetInstance() {
  static LogicSystem instance;
  return instance;
}

LogicSystem::LogicSystem() {
  registe_get_handler("/get_test",
                      [this](std::shared_ptr<HttpConnection> connection) {
                        on_recv_test_req(connection.get());
                      });

  registe_post_handler("/login/get_verifycode",
                       [this](std::shared_ptr<HttpConnection> connection) {
                         on_recv_verfiy_code_req(connection.get());
                       });

  registe_post_handler("/login/user_register",
                       [this](std::shared_ptr<HttpConnection> connection) {
                         on_recv_verfiy_code_req(connection.get());
                       });
}



bool LogicSystem::HandleGet(std::string const &url,
                            std::shared_ptr<HttpConnection> connection) {
  if(!get_handlers_.count(url)) {
    LogError("get req url {} not found", url);
    return false;
  }
  
  get_handlers_[url](connection);
  return true;
}

bool LogicSystem::HandlePost(std::string const &url,
                             std::shared_ptr<HttpConnection> connection) {
  if (!post_handlers_.count(url)) {
    LogError("post req url {} not found", url);
    return false;
  }

  post_handlers_[url](connection);
  return true;
}

void LogicSystem::registe_get_handler(std::string const &url,
                                      HttpHandler handler) {
  get_handlers_.insert(std::make_pair(url, handler));
}

void LogicSystem::registe_post_handler(std::string const &url,
                                       HttpHandler handler) {
  post_handlers_.insert(std::make_pair(url, handler));
}

void LogicSystem::on_recv_test_req(HttpConnection *connection) {
  ucbeast::ostream(connection->response_.body())
      << "receive get_test req \nhello client!\n";
  int i = 0;
  for (auto &elem : connection->url_params_) {
    i++;
    ucbeast::ostream(connection->response_.body())
        << "param" << i << " key is " << elem.first;
    ucbeast::ostream(connection->response_.body())
        << ", " << " value is " << elem.second << std::endl;
  }
}

void LogicSystem::on_recv_verfiy_code_req(HttpConnection *conn) {
  Json::Reader reader;
  Json::Value req, rsp;
  std::string body_str = boost::beast::buffers_to_string(conn->request_.body().data());
  bool parse_json = reader.parse(body_str, req);
  LogInfo("recv regist req, body: {}", body_str);

  if(!parse_json){
    rsp["error_code"] = ErrorCodes::Error_Json;
    LogWarn("parse json failed, body: {}", body_str);
  }
  if (!req.isMember("email")) {
    rsp["error_code"] = ErrorCodes::Error_Json;
    LogWarn("json item error: {}",body_str);
  } else {
    auto &client = VerifyGrpcClient::GetInstance();
    message::GetVerifyRsp rpc_rsp =
        client.GetVerifyCode(req["email"].asString());
    if (rpc_rsp.error_code() == message::ErrorCode::Error) {
      rsp["error_code"] = ErrorCodes::RPCFailed;
    } else {
      rsp["error_code"] = ErrorCodes::Success;
    }
  }
  rsp["email"] = req["email"];
  ucbeast::ostream(conn->response_.body()) << rsp.toStyledString();
  LogInfo("send verify code rsp to client: {}", rsp.toStyledString());
}

void LogicSystem::on_recv_user_regist_req(HttpConnection *conn){
  Json::Reader reader;
  Json::Value req, rsp;
  std::string body_str = boost::beast::buffers_to_string(conn->request_.body().data());
  LogInfo("recv regist req, body: {}", body_str);

  bool parse_json = reader.parse(body_str, req);
  if(!parse_json){
    rsp["error_code"] = ErrorCodes::Error_Json;
    LogWarn("parse json failed, body: {}", body_str);
  }
  if (!req.isMember("email") || !req.isMember("password") ||
      !req.isMember("verify_code")) {
    rsp["error_code"] = ErrorCodes::Error_Json;
    LogWarn("json item error: {}",body_str);
  } else {
    std::string req_code = req["verify_code"].asString();

    //todo check verify code(email and code)
    if (true) {
      rsp["error_code"] = ErrorCodes::Success;
    } else {
      rsp["error_code"] = ErrorCodes::VerifyCodeErr;
    }
  }
  
  // todo find user_name if exists
  rsp["email"] = req["email"];
  ucbeast::ostream(conn->response_.body()) << rsp.toStyledString();
  LogInfo("send user regist rsp to client: {}", rsp.toStyledString());
}


}  // namespace gate_server
}  // namespace uchat
