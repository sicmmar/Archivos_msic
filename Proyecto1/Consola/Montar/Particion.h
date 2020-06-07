#ifndef PARTICION_H
#define PARTICION_H

#include <QString>

class Particion{
public:
    Particion(QString path, QString nombre);
    QString path;
    QString iden;
    QString name;
    char disco;

};

#endif // PARTICION_H
