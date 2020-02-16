#pragma once

#ifdef _WIN32
  #include <winsock2.h>
#else
  #include <sys/socket.h>
#endif

#include <string>

class DatagramSocket {
public:
  explicit DatagramSocket(const std::string& addr);
  ~DatagramSocket();

  bool send(const std::string& payload);

protected:
  int fd_;
  sockaddr_storage addr_;
};
