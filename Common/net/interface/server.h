#ifndef _UCHAT_NET_SERVER_H_
#define _UCHAT_NET_SERVER_H_

class Server {
public:
  Server() = default;
  virtual ~Server() = default;

  virtual void Start() = 0;

  virtual void Stop();

};

#endif 
