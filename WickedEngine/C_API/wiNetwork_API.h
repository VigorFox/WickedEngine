#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiNetwork_Socket_t *wiNetwork_Socket;

typedef struct wiNetwork_Connection {
  unsigned char ipaddress[4];
  unsigned short port;
} wiNetwork_Connection;

wiNetwork_Socket wiNetwork_CreateSocket();
void wiNetwork_DestroySocket(wiNetwork_Socket sock);

bool wiNetwork_Send(const wiNetwork_Socket sock,
                    const wiNetwork_Connection *connection, const void *data,
                    size_t dataSize);
bool wiNetwork_ListenPort(const wiNetwork_Socket sock, unsigned short port);
bool wiNetwork_CanReceive(const wiNetwork_Socket sock,
                          long timeout_microseconds);
bool wiNetwork_Receive(const wiNetwork_Socket sock,
                       wiNetwork_Connection *connection, void *data,
                       size_t dataSize);

#ifdef __cplusplus
}
#endif
