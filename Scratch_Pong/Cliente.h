#ifndef CLIENTE_H
#define CLIENTE_H
#include <winsock.h>
class Cliente{
public:

    SOCKET s;
    sockaddr_in data;
    char buffer[1500];
    char buffer_in[1500];
    char ipdest[100];
    int port;
};

#endif // CLIENTE_H
