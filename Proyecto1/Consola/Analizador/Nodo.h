#ifndef NODO_H
#define NODO_H

#include "QString"
#include "QList"

class Nodo{
public:
    Nodo(int linea, int columna, int tipo, QString valor);
    void agregar(Nodo nodo);
    int linea;
    int columna;
    int tipo;
    QString valor;
    QList<Nodo> hijos;
};

#endif // NODO_H
