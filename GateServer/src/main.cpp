#include "acceptor.h"
#include "net_const.h"
#include <memory>


int main() {
  uc_ion_contex ioc{1};
  boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
  signals.async_wait(
      [&ioc](const boost::system::error_code &error, int signal_number) {
        if (error) {
          return;
        }
        ioc.stop();
      });

  std::shared_ptr<uchat::gate_server::Accptor> acc =
      std::make_shared<uchat::gate_server::Accptor>(ioc, 8889);
  acc->Start();
  ioc.run();

  return 0;
}