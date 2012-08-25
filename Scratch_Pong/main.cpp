#include <iostream>
//#include <winsock.h>
#include "Cliente.h"
#include "Conexion.h"
#include<stdio.h>
using namespace std;
#define VER 0x0101
//////////////////////////////////////////////////////////////
////////////CLIENTE ORIENTADO A CONEXION//////////////////////
//////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    Cliente Clocal, Cremoto;
    /*---------------CAPTURA IP y PUERTO-------------*/
    if(argc > 4){
        //PASO POR PARAMETROS
        memcpy(Clocal.ipdest,argv[1],100);
        printf("IP LOCAL: %s", Clocal.ipdest);
        Clocal.port = atoi(argv[2]);
        memcpy(Cremoto.ipdest,argv[3],100);
        printf("IP LOCAL: %s", Cremoto.ipdest);
        Clocal.port = atoi(argv[4]);
    }
    else{
        //MEDIANTE PROGRAMA
        printf("DAME UNA IP Y/O URL VALIDA:\n");
        scanf("%s", Clocal.ipdest);
        printf("DAME UN PUERTO:\n");
        scanf("%d",&Clocal.port);
        printf("DAME UNA IP Y/O URL VALIDA:\n");
        scanf("%s", Cremoto.ipdest);
        printf("DAME UN PUERTO:\n");
        scanf("%d",&Cremoto.port);
    }
    Conexion con;
    con.Conecta(Clocal,Cremoto);

    WSACleanup();

    return 0;
}

