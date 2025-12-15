#include "wiNetwork_API.h"
#include "wiNetwork.h"

using namespace wi::network;

struct wiNetwork_Socket_t {
  Socket socket;
};

extern "C" {

wiNetwork_Socket wiNetwork_CreateSocket() {
  wiNetwork_Socket_t *s = new wiNetwork_Socket_t();
  if (CreateSocket(&s->socket)) {
    return s;
  }
  delete s;
  return nullptr;
}

void wiNetwork_DestroySocket(wiNetwork_Socket sock) {
  if (sock)
    delete sock;
}

bool wiNetwork_Send(const wiNetwork_Socket sock,
                    const wiNetwork_Connection *connection, const void *data,
                    size_t dataSize) {
  if (!sock || !connection)
    return false;
  Connection c;
  c.ipaddress[0] = connection->ipaddress[0];
  c.ipaddress[1] = connection->ipaddress[1];
  c.ipaddress[2] = connection->ipaddress[2];
  c.ipaddress[3] = connection->ipaddress[3];
  c.port = connection->port;
  return Send(&sock->socket, &c, data, dataSize);
}

bool wiNetwork_ListenPort(const wiNetwork_Socket sock, unsigned short port) {
  if (!sock)
    return false;
  return ListenPort(&sock->socket, port);
}

bool wiNetwork_CanReceive(const wiNetwork_Socket sock,
                          long timeout_microseconds) {
  if (!sock)
    return false;
  return CanReceive(&sock->socket, timeout_microseconds);
}

bool wiNetwork_Receive(const wiNetwork_Socket sock,
                       wiNetwork_Connection *connection, void *data,
                       size_t dataSize) {
  if (!sock || !connection)
    return false;
  Connection c;
  bool result = Receive(&sock->socket, &c, data, dataSize);
  if (result) {
    connection->ipaddress[0] = c.ipaddress[0];
    connection->ipaddress[1] = c.ipaddress[1];
    connection->ipaddress[2] = c.ipaddress[2];
    connection->ipaddress[3] = c.ipaddress[3];
    connection->port = c.port;
  }
  return result;
}

} // extern "C"
