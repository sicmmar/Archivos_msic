#include "Nodo.h"
#include <qdebug.h>

Nodo::Nodo(int l, int c, int t, QString v){
    linea = l;
    columna = c;
    tipo = t;
    valor = v;
    hijos = QList<Nodo>();
}

void Nodo::agregar(Nodo nd){
    this->hijos.append(nd);
}
