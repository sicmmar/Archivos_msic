#ifndef USUARIO_H
#define USUARIO_H

#include "Montar/Particion.h"

class Usuario{
public:
    Usuario();
    bool hayUsuario;
    char nombre[10];
    char passwd[10];
    char grupo[10];
    Particion particion;
};

#endif // USUARIO_H
