#ifndef EJECUTAR_H
#define EJECUTAR_H

#include "Analizador/Nodo.h"
#include "Montar/Montar.h"
#include <iostream>
#include "Usuario.h"

using namespace::std;

class Ejecutar{
public:
    Nodo *raiz;
    Ejecutar();
    void ejecutar(Nodo *raiz, Montar *listaParticiones, Usuario *usuario);
    Montar *listaParticiones;
    Usuario *usuario;


private:
    void recorrer(Nodo *raiz);
    void mkdisk(Nodo *raiz);
    void rmdisk(Nodo *raiz);
    void fdisk(Nodo *raiz);
    void mount(Nodo *raiz);
    void unmount(Nodo *raiz);
    void rep(Nodo *raiz);
    void pause();
    void mkfs(Nodo *raiz);
    void login(Nodo *raiz);
    void logout();
    void mkgrp(Nodo *raiz);
    void rmgrp(Nodo *raiz);
    void mkusr(Nodo *raiz);
    void rmusr(Nodo *raiz);
    void chmod(Nodo *raiz);
    void mkfile(Nodo *raiz);;
    void cat(Nodo *raiz);
    void rem(Nodo *raiz);
    void edit(Nodo *raiz);
    void ren(Nodo *raiz);
    void mkdir(Nodo *raiz);
    void cp(Nodo *raiz);
    void mv(Nodo *raiz);
    void chown(Nodo *raiz);
    void chgrp(Nodo *raiz);
    void find(Nodo *raiz);
    int size = 0;
    QString fit = "", unit = "", path = "", type = "";
    QString del = "", nombre = "", add = "", id = "";
    QString usr = "", pwd = "", grp = "", ugo = "";
    bool R = false, P = false;
    QString cont = "", fileParam = "", dest = "", ruta = "";
    void limpiarVariables();
    void colocarParametros(Nodo *raiz);
    bool parametrosCorrectos(int comando);
    bool parametrosObligatorios(int comando);
    string obtenerFecha();
    string obtenerFirma();
    string intToString(int num);
    bool reporteValido(QString nombre);
    QString traducirPermisos(int permisos);
};

#endif // EJECUTAR_H
