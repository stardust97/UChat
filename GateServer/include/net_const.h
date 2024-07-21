#ifndef _UCHAT_COMMON_NET_CONST_H_
#define _UCHAT_COMMON_NET_CONST_H_

#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>


namespace ucbeast = boost::beast;         // from <boost/beast.hpp>
namespace uchttp = ucbeast::http;           // from <boost/beast/http.hpp>
namespace ucasio = boost::asio;            // from <boost/asio.hpp>

using uctcp = ucasio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using uc_ion_contex = ucasio::io_context; // from <boost/asio/io_context.hpp>
using uc_error_code = boost::system::error_code;



#endif