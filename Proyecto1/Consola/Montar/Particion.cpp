#include "Particion.h"
#include "QString"
#include <string>

Particion::Particion(QString path, QString nombre, Partition part){
    this->name = nombre;
    this->path = path;
    this->particion = part;
}
