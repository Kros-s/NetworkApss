#include <iostream>
#include <winsock.h>
#include<stdio.h>
using namespace std;
#define VER 0x0101
//////////////////////////////////////////////////////////////
////////////CLIENTE ORIENTADO A CONEXION//////////////////////
//////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKET s;
    sockaddr_in data;
    char buffer[1500];
    char buffer_in[1500];
    char ipdest[100];
    int port;
    /*---------------CAPTURA IP y PUERTO-------------*/
    if(argc > 2){
        //PASO POR PARAMETROS
        memcpy(ipdest,argv[1],100);
        printf("IP: %s", ipdest);
        port = atoi(argv[2]);

    }
    else{
        //MEDIANTE PROGRAMA
        printf("DAME UNA IP Y/O URL VALIDA:\n");
        scanf("%s", ipdest);
        printf("DAME UN PUERTO:\n");
        scanf("%d",&port);

    }
    ////////////////////////INICALIZANDO SOCKET/////////////

    long int *ap;
    ap=(long int*)buffer;
    sprintf(buffer+4,"broadcast \"hola\"");
    *ap=htonl(strlen(buffer+4));

    printf(" %x%x%x%x ",(int)buffer[0],(int)buffer[1],(int)buffer[2],buffer[3]);
    printf("%s",buffer+4);


    if(WSAStartup(VER,&wsaData)!=0)
        perror("ERROR AL CARGAR LIBRERIAS");
    s = socket(PF_INET, SOCK_STREAM, 0);
    data.sin_family=AF_INET;
    data.sin_port=htons(port);
    data.sin_addr.s_addr = inet_addr(ipdest);// PENDIENTE IPDESTINO
    if(connect(s,(const sockaddr*)&data,sizeof(data))!=0)
        perror("NO CONECTION ESTABLISHED");
    // NO SE SI NO ESTA REALIZANDO EL ENVIO YA QUE NO APARECE EN NC
    if(send(s,buffer,strlen(buffer)+1,0)==-1) // PQ PARECE Q ESTE NO LO ENVIA Y EL OTRO SI ??
        perror("EOOR NOT SEND");
    if(send(s,buffer,sizeof(buffer)+1,0)==-1)
        perror("EOOR NOT SEND");
    if((recv(s,buffer_in,sizeof(buffer_in),0))!= -1)
        perror("ERROR AL RECIBIR");
    printf("\n\nDATA : \n%s",buffer_in);

    WSACleanup();



    return 0;
}

