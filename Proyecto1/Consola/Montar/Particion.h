#ifndef PARTICION_H
#define PARTICION_H

#include <QString>

struct Partition{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
};

class Particion{
public:
    Particion(QString path, QString nombre, Partition particion);
    QString path;
    QString iden;
    QString name;
    Partition particion;
    char disco;

};

#endif // PARTICION_H
