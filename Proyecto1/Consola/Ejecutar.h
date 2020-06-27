#ifndef EJECUTAR_H
#define EJECUTAR_H

#include "Analizador/Nodo.h"
#include "Montar/Montar.h"
#include <iostream>
#include "Usuario.h"

using namespace::std;


//struct

struct MBR{
    int mbr_tamano;
    char mbr_fecha_creacion[32];
    int mbr_signature;
    char disk_fit;
    Partition mbr_partition[4];
};

struct SuperBlock{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_block_count;
    int s_free_inodes_count;
    char s_mtime[32];
    char s_umtime[32];
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
    int s_journal_count;
};

struct Inode{
    int i_id;
    int i_uid;
    int i_gid;
    int i_size;
    char i_atime[32];
    char i_mtime[32];
    int i_block[15];
    int i_type;
    int i_perm;
};

struct Content{
    char b_name[12];
    int b_inode;
};

struct Bloque_Carpeta{
    int b_id;
    Content b_content[4];
};

struct Bloque_Archivo{
    int b_id;
    char b_content[64];
};

struct Bloque_Apuntador{
    int b_id;
    int b_pointers[16];
};

struct Journal{
    char j_fecha_hora[32];
    char j_user[12];
    char j_operation[256];
};


class Ejecutar{
public:
    Nodo *raiz;
    Ejecutar();
    void ejecutar(Nodo *raiz, Montar *listaParticiones, Usuario *usuario);
    Montar *listaParticiones;
    Usuario *usuario;
    bool R, P;


private:
    void recorrer(Nodo *raiz);
    void ponerP(Nodo *raiz);
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
    void colocar(QString path, int inodo_actual, SuperBlock SB, FILE* disco);
};

#endif // EJECUTAR_H
