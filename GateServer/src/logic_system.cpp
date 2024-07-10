#include "logic_system.h"

#include <iostream>
#include <utility>

#include "http_connection.h"


namespace uchat {
namespace gate_server {

LogicSystem& LogicSystem::GetInstance() {
  static LogicSystem instance;
  return instance;
}

LogicSystem::LogicSystem() {
  RegisterHandler(
      "/get_test", [](std::shared_ptr<HttpConnection> connection) {
        ucbeast::ostream(connection->response_.body())
            << "receive get_test req \nhello client!\n";
        int i = 0;
        for (auto &elem : connection->url_params_) {
          i++;
          ucbeast::ostream(connection->response_.body())
              << "param" << i << " key is " << elem.first;
          ucbeast::ostream(connection->response_.body())
              << ", "
              << " value is " << elem.second << std::endl;
        }
      });
}

LogicSystem::~LogicSystem() {

}

bool LogicSystem::HandleGet(std::string const &url,
                            std::shared_ptr<HttpConnection> connection) {
  if(!get_handlers_.count(url)) {
    std::cout << "not found url: " << url << std::endl;
    return false;
  }
  
  get_handlers_[url](connection);
  return true;
}

void LogicSystem::RegisterHandler(std::string const &url, HttpHandler handler) {
  get_handlers_.insert(std::make_pair(url, handler));
}

}  // namespace gate_server
}  // namespace uchat
