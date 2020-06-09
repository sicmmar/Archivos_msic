#ifndef EJECUTAR_H
#define EJECUTAR_H

#include "Analizador/Nodo.h"
#include "Montar/Montar.h"
#include <iostream>
using namespace::std;

class Ejecutar{
public:
    Nodo *raiz;
    Ejecutar();
    void ejecutar(Nodo *raiz, Montar *listaParticiones);
    Montar *listaParticiones;

private:
    void recorrer(Nodo *raiz);
    void mkdisk(Nodo *raiz);
    void rmdisk(Nodo *raiz);
    void fdisk(Nodo *raiz);
    void mount(Nodo *raiz);
    void unmount(Nodo *raiz);
    void rep(Nodo *raiz);
    int size = 0;
    QString fit = "", unit = "", path = "", type = "";
    QString del = "", nombre = "", add = "", id = "";
    void limpiarVariables();
    void colocarParametros(Nodo *raiz);
    bool parametrosCorrectos(int comando);
    bool parametrosObligatorios(int comando);
    string obtenerFecha();
    string obtenerFirma();
    string intToString(int num);
};

#endif // EJECUTAR_H
