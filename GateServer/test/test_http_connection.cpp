#include <string>
#define ENABLE_TEST
#include "../include/http_connection.h"
#include <gtest/gtest.h>

using namespace uchat::gate_server;

TEST(http_conn, encode) {
  uc_ion_contex ioc;
  HttpConnection conn(ioc);
  std::string url = "key1=%20 key2=1F";
  std::string url_encode = conn.url_encode(url);
  std::string url_decode = conn.url_decode(url_encode);
  EXPECT_EQ(url_encode, "key1%3D%2520+key2%3D1F");
  EXPECT_EQ(url_decode, "key1=%20 key2=1F");

  // url = "key1=%C2+key2=%3E";
  // url_decode = conn.url_decode(url);
  // url_encode = conn.url_encode(url_decode);
  // EXPECT_EQ(url_decode, "key1=194 key2=62");
  // EXPECT_EQ(url_encode, "key1=%C2+key2=%3E");

  // url = "key1=%C+key2=%3E";
  // url_decode = conn.url_decode(url);
  // url_encode = conn.url_encode(url_decode);
  // EXPECT_EQ(url_decode, "key1=15 key2=62");
  // EXPECT_EQ(url_encode, "key1=%0C+key2=%3E");
}

//bug
TEST(http_conn, parse_param) {
  uc_ion_contex ioc;
  HttpConnection conn(ioc);
  std::string url = "127.0.0.1:/8889/login/"
                    "verify?email=12345678@qq.com&password=qwerasdf&sms=078956";
  conn.request_.target(url);
  conn.PreParseGetParam();
  EXPECT_EQ(conn.url_, "/login/verify");
  EXPECT_EQ(conn.url_params_["email"], "12345678@qq.com");
  EXPECT_EQ(conn.url_params_["password"], "qwerasdf");
  EXPECT_EQ(conn.url_params_["sms"], "078956");
}
