#ifndef MONTAR_H
#define MONTAR_H

#include "QList"
#include <QString>
#include "Particion.h"
#include "Disco.h"
#include <stdlib.h>

using namespace::std;

class Montar{
public:
    Montar();
    void agregarParticion(Particion nueva);
    void quitarParticion(QString id, string fecha);
    int buscarParticion(QString nombre, QString path, QString iden);
    Particion devolverParticion(QString iden);
    string fechaUnmount;
    QList<Disco> listaDiscos;
    QList<Particion> listaParticion;
    int buscarDiscos(QString path);
};

#endif // MONTAR_H
