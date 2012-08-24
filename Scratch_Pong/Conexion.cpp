#include "Conexion.h"
#include <stdio.h>
#define VER 0x0101
WSADATA wsaData;
void Conexion::Conecta(Cliente local, Cliente remoto){
    Clocal = local;
    Cremoto = remoto;
    Prepare();
}
void Conexion::Prepare(){
    if(WSAStartup(VER,&wsaData)!=0)
            perror("ERROR AL CARGAR LIBRERIAS");
    // INICIALIZANDO SOCKETS
    Clocal.s = socket(PF_INET, SOCK_STREAM, 0);
    Cremoto.s= socket(PF_INET, SOCK_STREAM, 0);
    Clocal.data.sin_family=AF_INET;
    Cremoto.data.sin_family=AF_INET;
    Clocal.data.sin_port=htons(Clocal.port);
    Cremoto.data.sin_port=htons(Cremoto.port);
    Clocal.data.sin_addr.s_addr = inet_addr(Clocal.ipdest);
    Cremoto.data.sin_addr.s_addr = inet_addr(Cremoto.ipdest);
    //ESTABLECIENDO CONEXION LOCAL
    if(connect(Clocal.s,(const sockaddr*)&Clocal.data,sizeof(Clocal.data))!=0)
        perror("NO CONECTION ESTABLISHED");
    //ESTABLECIENDO CONEXION REMOTA
    if(connect(Cremoto.s,(const sockaddr*)&Cremoto.data,sizeof(Cremoto.data))!=0)
        perror("NO CONECTION ESTABLISHED");
}
