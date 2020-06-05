#ifndef GRAFICAR_H
#define GRAFICAR_H

#include "Nodo.h"
#include <fstream>
#include <iostream>

class Graficar
{
public:
    Graficar(Nodo *raiz);
    Nodo *raiz;
    int contador;
    QString grafo;
    QString graficar();
    void recorrerAST(QString padre, Nodo *hijo);
    QString escapar(QString cadena);
    void generarImagen();

};

#endif // GRAFICAR_H
