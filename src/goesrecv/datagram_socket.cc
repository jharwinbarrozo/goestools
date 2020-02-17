#include "datagram_socket.h"

#ifdef _WIN32
  #include <ws2def.h>
  #include <ws2tcpip.h>
#else
  #include <netdb.h>
  #include <netinet/in.h>
  #include <sys/socket.h>
#endif
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>

DatagramSocket::DatagramSocket(const std::string& addr) {
  std::string schema;
  std::string host;
  std::string port;
  size_t pos;

  pos = addr.find("://");
  if (pos != std::string::npos) {
    schema = addr.substr(0, pos);
    host = addr.substr(pos + 3);
  } else {
    host = addr;
  }

  pos = host.find(':');
  if (pos != std::string::npos) {
    port = host.substr(pos + 1);
    host = host.substr(0, pos);
  }

  if (host.empty()) {
    host = "localhost";
  }

  if (port.empty()) {
    port = "8125";
  }

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  if (schema == "udp4") {
    hints.ai_family = AF_INET;
  } else if (schema == "udp6") {
    hints.ai_family = AF_INET6;
  } else {
    hints.ai_family = AF_UNSPEC;
  }
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = 0;
  #ifdef AI_ADDRCONFIG
    hints.ai_flags = AI_ADDRCONFIG;
  #endif
  struct addrinfo* res = nullptr;
  auto rv = getaddrinfo(host.c_str(), port.c_str(), &hints, &res);
  if (rv < 0) {
    throw std::runtime_error("unable to resolve: " + host);
  }

  #ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(1, 1), &wsa_data)) {
      throw std::runtime_error("unable to initialise winsock");
    }
  #endif

  auto fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if (fd < 0) {
    throw std::runtime_error("unable to create socket");
  }

  fd_ = fd;
  memset(&addr_, 0, sizeof(addr_));
  memcpy(&addr_, res->ai_addr, res->ai_addrlen);
}

DatagramSocket::~DatagramSocket() {
  #ifdef _WIN32
    closesocket(fd_);
    WSACleanup();
  #else
    close(fd_);
  #endif
}

bool DatagramSocket::send(const std::string& payload) {
  auto rv = sendto(
      fd_,
      payload.c_str(),
      payload.size(),
      0,
      (const sockaddr*) &addr_,
      sizeof(addr_));
  return rv >= 0;
}
