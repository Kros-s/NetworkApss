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
         if(connect(Cremoto.s,(const sockaddr*)&Cremoto.data,sizeof(Cremoto.data))!=0)
        perror("NO CONECTION ESTABLISHED");
    //ENVIANDO DATOS 
    int help;
    while(1){
        printf("\n\n---------------RECIBIENDO DATOS LOCALES----------");
        /////////DATOS RECIBIDOS
        if((help=recv(Clocal.s,Clocal.buffer_in,sizeof(Clocal.buffer_in),0))== -1)
            perror("ERROR AL RECIBIR");
        Clocal.buffer_in[help]=0;
        printf("\n\nDATA : \n%s\n",Clocal.buffer_in+4);
         ///ENVIAMOS LO RECIBIDO
        //POR AHORA ESTAMOS ENVIANDO LO MISMO QUE RECIBIMOS 
        printf("\n\n---------------ENVIANDO DATOS LOCALES----------");
        if(send(Cremoto.s,Clocal.buffer_in,help,0)==-1)
            perror("ERROR NOT SEND");
            printf(" %x%x%x%x ",(int)Clocal.buffer_in[0],(int)Clocal.buffer_in[1],(int)Clocal.buffer_in[2],Clocal.buffer_in[3]);
            printf("%s\n",Clocal.buffer_in+4);
    /*ERROR AL RECIBIR CON SCRATCH LAS VARIABLES CADA UNA DE ELLAS TIENE QUE TENER SU PROPIO IDENTIFICADOR*/
        
               
    }
}
