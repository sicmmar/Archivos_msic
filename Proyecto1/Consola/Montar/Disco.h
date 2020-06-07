#ifndef DISCO_H
#define DISCO_H

#include <QString>

class Disco{
public:
    Disco(QString path);
    QString path;
    int numParticiones;
};

#endif // DISCO_H
