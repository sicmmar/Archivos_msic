#ifndef EJECUTAR_H
#define EJECUTAR_H

#include "Analizador/Nodo.h"
#include <iostream>
using namespace::std;

class Ejecutar{
public:
    Nodo *raiz;
    Ejecutar();
    void ejecutar(Nodo *raiz);

private:
    void recorrer(Nodo *raiz);
    void mkdisk(Nodo *raiz);
    void rmdisk(Nodo *raiz);
    void fdisk(Nodo *raiz);
    void mount(Nodo *raiz);
    void unmount(Nodo *raiz);
    void rep(Nodo *raiz);
    void exec(Nodo *raiz);
    QString size = "", fit = "", unit = "", path = "", type = "";
    QString del = "", nombre = "", add = "", id = "";
    void limpiarVariables();
    void colocarParametros(Nodo *raiz);
    bool parametrosCorrectos(int comando);
    bool parametrosObligatorios(int comando);
    string obtenerFecha();
    string obtenerFirma();

};

#endif // EJECUTAR_H
