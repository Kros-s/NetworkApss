#ifndef CONEXION_H
#define CONEXION_H
#include<winsock.h>
#include "Cliente.h"
class Conexion{
private:
    Cliente Clocal;
    Cliente Cremoto;
public:
    void Conecta(Cliente local, Cliente remoto);
    void Prepare();

};

#endif // CONEXION_H
