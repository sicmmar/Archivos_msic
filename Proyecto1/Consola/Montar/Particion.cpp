#include "Particion.h"
#include "QString"
#include <string>

Particion::Particion(QString path, QString nombre, Partition part){
    this->name = nombre;
    this->path = path;
    this->Fecha = "";
    this->particion = part;
}

Particion::Particion(){
    this->name = "NULL";
    this->path = "NULL";
}
