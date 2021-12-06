#ifndef EVEIO_NET_TCPCONNECTION_HPP
#define EVEIO_NET_TCPCONNECTION_HPP

#include "eveio/Result.hpp"
#include "eveio/String.hpp"
#include "eveio/Time.hpp"
#include "eveio/net/InetAddr.hpp"
#include "eveio/net/Socket.hpp"

namespace eveio {
namespace net {

class TcpConnection {
public:
  typedef detail::native_socket_type native_socket_type;
  static constexpr native_socket_type InvalidSocket = detail::InvalidSocket;

private:
  native_socket_type conn_handle;
  Time create_time;
  InetAddr peer_addr;

  TcpConnection(native_socket_type conn, const InetAddr &addr) noexcept
      : conn_handle(conn), create_time(Time::Now()), peer_addr(addr) {}

public:
  static Result<TcpConnection> Connect(const InetAddr &peer) noexcept;

  TcpConnection(const TcpConnection &) = delete;
  TcpConnection &operator=(const TcpConnection &) = delete;

  TcpConnection(TcpConnection &&other) noexcept;
  TcpConnection &operator=(TcpConnection &&other) noexcept;

  ~TcpConnection() noexcept;

  Time CreateTime() const noexcept { return create_time; }
  const InetAddr &PeerAddr() const noexcept { return peer_addr; }

  int Send(StringRef data) const noexcept;
  int Send(const void *buf, size_t byte) const noexcept;
  int Receive(void *buf, size_t cap) const noexcept;

  void CloseWrite() const noexcept;
  bool IsClosed() const noexcept;

  bool SetNoDelay(bool on) const noexcept;
  bool SetNonblock(bool on) const noexcept;
  bool SetKeepAlive(bool on) const noexcept;

  native_socket_type native_socket() const noexcept { return conn_handle; }
  operator native_socket_type() const noexcept { return conn_handle; }

  friend class TcpSocket;
};

} // namespace net
} // namespace eveio

#endif // EVEIO_NET_TCPCONNECTION_HPP