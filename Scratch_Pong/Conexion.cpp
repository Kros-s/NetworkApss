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
    int help;
    if(connect(Clocal.s,(const sockaddr*)&Clocal.data,sizeof(Clocal.data))!=0)
        perror("NO CONECTION ESTABLISHED");

    if(connect(Cremoto.s,(const sockaddr*)&Cremoto.data,sizeof(Cremoto.data))!=0)
        perror("NO CONECTION ESTABLISHED");
    while(1){


    //if((help=recv(Clocal.s,Clocal.buffer_in,sizeof(Clocal.buffer_in),0))== -1)
      //  perror("ERROR AL RECIBIR");
    //Clocal.buffer_in[help]=0;
    //printf("\n\nDATA LOCAL  : \n%s",Clocal.buffer_in+4);

    // PERFECTO YA RECIBO DATOS :D
    // VEAMOS AHORA EL SEGUNDO SOCKET
    /*---INTENTAREMOS PRIMERO CON UN SOCKET LOCAL HACIENDO Q SE DUPLIQUE W */
    //ESTABLECIENDO CONEXION REMOTA


    if((help=recv(Cremoto.s,Cremoto.buffer_in,sizeof(Cremoto.buffer_in),0))== -1)
        perror("ERROR AL RECIBIR");
    Cremoto.buffer_in[help]=0;
    printf("\n\nDATA REMOTO : \n%s",Cremoto.buffer_in+4);
    //ENVIANDO x VIA REMOTA
    memcpy(Clocal.buffer,Cremoto.buffer_in,1500);
    printf("\n\nDATA ENVIO  : \n%s",Cremoto.buffer+4);
    if(send(Clocal.s,Clocal.buffer,strlen(Clocal.buffer+4)+5,0)==-1)
            perror("EOOR NOT SEND");
    }
}
