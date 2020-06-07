#ifndef MONTAR_H
#define MONTAR_H

#include "QList"
#include <QString>
#include "Particion.h"
#include "Disco.h"

class Montar{
public:
    Montar();
    void agregarParticion(Particion nueva);
    void quitarParticion(QString id);
    int buscarParticion(QString nombre, QString path, QString iden);
    QList<Disco> listaDiscos;
    QList<Particion> listaParticion;
    int buscarDiscos(QString path);
};

#endif // MONTAR_H
