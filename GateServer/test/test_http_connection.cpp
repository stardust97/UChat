#include <iostream>
#include <string>
#define ENABLE_TEST
#include "../include/http_connection.h"

using namespace uchat::gate_server;


int main() {

  uc_ion_contex ioc;
  HttpConnection conn(ioc);
  // std::string url = "key1=%20+key2=%1F";
  // std::string url_decode = conn.UrlDecode(url);
  // std::string url_encode = conn.UrlEncode(url_decode);
  // url_decode = conn.UrlDecode(url);

  // std::cout << url_decode << std::endl;
  // std::cout << url_encode << std::endl;
  // std::cout << url_decode << std::endl;

  // url = "key1=%C2+key2=%3E";
  // url_decode = conn.UrlDecode(url);
  // url_encode = conn.UrlEncode(url_decode);
  // url_decode = conn.UrlDecode(url);

  // std::cout << url_decode << std::endl;
  // std::cout << url_encode << std::endl;
  // std::cout << url_decode << std::endl;

  std::string url2 = "127.0.0.1:/8889/get_test?key1=value1&key2=value2";
  std::string res = url2.substr(25,36-24);
  std::cout << "res: " << res << std::endl;
  conn.request_.target(url2);
  conn.PreParseGetParam();
  for (auto &it : conn.url_params_) {
    std::cout << it.first << ": " << it.second << std::endl;
  }

  return 0;
}