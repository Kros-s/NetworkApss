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
    sprintf(buffer+4,"broadcast \"Hola q ase\"");
    *ap=htonl(strlen(buffer+4));
    //EL PROBLEMA ES QUE DETECTA COMO CARACTER VACIO LOS 3 PRIMEROS 000
    //printf(" %x%x%x%x ",(int)buffer[0],(int)buffer[1],(int)buffer[2],buffer[3]);
    //    printf("%s",buffer+4);
    /////////////INICIALIZANDO SOCKET
    if(WSAStartup(VER,&wsaData)!=0)
        perror("ERROR AL CARGAR LIBRERIAS");
    s = socket(PF_INET, SOCK_STREAM, 0);
    printf("SOCKET %d \n ",s);
    data.sin_family=AF_INET;
    data.sin_port=htons(port);
    data.sin_addr.s_addr = inet_addr(ipdest);
    //ESTABLECIENDO CONEXION
    if(connect(s,(const sockaddr*)&data,sizeof(data))!=0)
        perror("NO CONECTION ESTABLISHED");
    //STRLEN SOLO DETECTA A PARTIR DEL 4TO BYTE X ESO NO FURULABA
    int help;
    while(1){
             printf("HOLA");
        /////////DATOS RECIBIDOS
        if((help=recv(s,buffer_in,sizeof(buffer_in),0))== -1)
            perror("ERROR AL RECIBIR");
        buffer_in[help]=0;
        printf("\n\nDATA : \n%s\n",buffer_in+4);
        
        ///ENVIAMOS LO RECIBIDO
        if(send(s,buffer_in,help,0)==-1)
            perror("ERROR NOT SEND");
            printf(" %x%x%x%x ",(int)buffer_in[0],(int)buffer_in[1],(int)buffer_in[2],buffer_in[3]);
            printf("%s\n",buffer_in+4);
    
        
    }       
    WSACleanup();


    system("pause");
    return 0;
}

