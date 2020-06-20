#include "Ejecutar.h"
#include <iostream>
#include <fstream>
#include "time.h"
#include "ctime"
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include "Montar/Particion.h"
#include "Analizador/parser.h"
#include "Analizador/scanner.h"
#include "Analizador/Graficar.h"


extern int yyparse(); //
extern Nodo *raiz; // Raiz del arbol
extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;

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

Ejecutar::Ejecutar(){
    this->raiz = NULL;
    this->usuario = new Usuario();
}

const int magic_number = 0xEF53;
const int inode_size = sizeof (Inode);
const int block_size = 68;
const char unUno = '1';
const char unCero = '0';

void Ejecutar::ejecutar(Nodo *raiz, Montar *lista, Usuario *usuario){
    this->listaParticiones = lista;
    this->usuario = usuario;
    this->raiz = raiz;
    this->recorrer(raiz);
}

void Ejecutar::recorrer(Nodo *raiz){
    switch (raiz->tipo) {
    case -1: //lista de comandos
        for(int i = 0; i < raiz->hijos.length(); i++){
            Nodo n = raiz->hijos.at(i);
            recorrer(&n);
        }
        break;
    case -2: //lista de parametros
        for(int i = 0; i < raiz->hijos.length(); i++){
            Nodo n = raiz->hijos.at(i);
            recorrer(&n);
        }
        break;
    case 0: //mkdisk
        {
            Nodo param = raiz->hijos.at(0); //envio el nodo de lista de parametros
            this->mkdisk(&param);
        }
        break;
    case 5: //rmdisk
        {
            Nodo param = raiz->hijos.at(0); //envio el nodo de lista de parametros
            this->rmdisk(&param);
        }
        break;
    case 6: //fdisk
    {
        Nodo param = raiz->hijos.at(0); //envio el nodo de lista de parametros
        this->fdisk(&param);
    }
        break;
    case 11: //mount
    {
        Nodo param = raiz->hijos.at(0); //envio el nodo de lista de parametros
        this->mount(&param);
    }
        break;
    case 12: //unmount
    {
        Nodo param = raiz->hijos.at(0); //envio el nodo de lista de parametros
        this->unmount(&param);
    }
        break;
    case 14: //rep
    {
        Nodo param = raiz->hijos.at(0);
        this->rep(&param);
    }
        break;
    case 49: //pause
    {
        this->pause();
    }
        break;
    case 63: // parametro r
    {
        this->R = true;
    }
        break;
    case 64: // parametro p
    {
        this->P = true;
    }
        break;
    case 31: //mkfs
    {
        Nodo param = raiz->hijos.at(0); //envio el nodo de lista de parametros
        this->mkfs(&param);
    }
        break;
    case 32: // login
    {
        Nodo param = raiz->hijos.at(0); //envio el nodo de lista de parametros
        this->login(&param);
    }
        break;
    case 33: // logout
    {
        this->logout();
    }
        break;
    case 34: // mkgrp
    {
        Nodo param = raiz->hijos.at(0); //envio el nodo de lista de parametros
        this->mkgrp(&param);
    }
        break;
    }
}

void Ejecutar::mkdisk(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    if(parametrosObligatorios(1)){
        if(this->fit == ""){
            cout << " ::Colocando el primer ajuste ..." << endl;
            this->fit = "FF";
        }

        if(this->unit == ""){
            cout << " ::Colocando MegaBytes como unidad ..." << endl;
            this->unit = "M";
        }

        MBR mbr;
        strcpy(mbr.mbr_fecha_creacion,obtenerFecha().c_str());
        mbr.mbr_signature = atoi(obtenerFirma().c_str());
        mbr.disk_fit = this->fit.toUpper().toStdString()[0];

        int tamano = 0;
        if(this->unit.toUpper() == "M") tamano = this->size * (1024 * 1024);
        else if(this->unit.toUpper() == "K") tamano = this->size * 1024;
        mbr.mbr_tamano = tamano;

        if(this->path.split(".")[1].toUpper() == "DISK"){
            char comando[500];
            QStringList arr = this->path.split("/");
            QString direccion = "";
            int i = 1;
            while (i < (arr.length()-1)){
                direccion+= "/" + arr[i];
                strcpy(comando, ("cd " + direccion).toStdString().c_str());
                if(system(comando)){ //error
                    strcpy(comando, ("mkdir " + direccion).toStdString().c_str());
                    cout << " ::Creando " << direccion.toStdString() << " como directorio " << endl;
                    system(comando);
                }
                i++;
            }

            for(int i = 0; i < 4; i++){
                mbr.mbr_partition[i].part_fit = 'N';
                mbr.mbr_partition[i].part_name[0] = 'N';
                mbr.mbr_partition[i].part_size = 0;
                mbr.mbr_partition[i].part_type = 'N';
                mbr.mbr_partition[i].part_start = -1;
                mbr.mbr_partition[i].part_status = 'I';
            }

            QString path2 = this->path.replace(".disk", "_raid.disk");
            this->path.replace("_raid.disk", ".disk");
            char dir1[this->path.length()], dir2[path2.length()];
            strcpy(dir1,this->path.toStdString().c_str());
            strcpy(dir2,path2.toStdString().c_str());
            FILE* disco1 = fopen(dir1, "wb");
            FILE* disco2 = fopen(dir2, "wb");
            if(disco1 != 0 && disco2 != 0){
                int fin=(tamano/1024);
                char buffer[1024];
                int i=0;
                for(i=0;i<1024;i++){
                    buffer[i]='0';
                }

                int j = 0;
                while(j != fin){
                    fwrite(&buffer,1024 , 1, disco1);
                    fwrite(&buffer, 1024, 1, disco2);
                    j++;
                }
            }
            fclose(disco1);
            fclose(disco2);

            FILE* f1= fopen(dir1, "r+b");
            FILE* f2= fopen(dir2, "r+b");
            fseek(f1,0,SEEK_SET);// estableciendo puntero al inicio
            fseek(f2,0,SEEK_SET);// estableciendo puntero al inicio
            if(f1 != 0 && f2 != 0){
                fwrite(&mbr, sizeof(MBR), 1, f1);//escribiendo la estructura del MBR
                fwrite(&mbr, sizeof(MBR), 1, f2);
                cout << " ::Discos en " << this->path.toStdString() << " creado con exito" << endl;
            }

            fclose(f1);
            fclose(f2);

        }else cout << "error: la extension para la creacion del disco es incorrecta " << endl;

    }
    //mkdisk -path=/home/fheiurh/dje/disco.disk -size=487
}

void Ejecutar::rmdisk(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    if(parametrosObligatorios(8)){
        char comando[500];
        strcpy(comando, ("find " + this->path).toStdString().c_str());
        if(system(comando)) cout << "error: compruebe la ruta, el disco no existe" << endl;
        else{
            cout << " ::Confirmar eliminacion, seguro que desea eliminar? [Y/n]";
            string confirm;
            getline(cin, confirm);
            if(confirm == "n" || confirm == "N") cout << " ::El disco no se ha eliminado" << endl;
            else{
                strcpy(comando, ("rm " + this->path).toStdString().c_str());
                if(!system(comando)) cout << " ::Disco eliminado" << endl;
            }
        }
    }
}

void Ejecutar::fdisk(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    int accionEjecutada = 0;

    if(this->path != "" && this->nombre != ""){
       char comando[500];
       strcpy(comando,this->path.toStdString().c_str());
       FILE* d1 = fopen(comando, "r+b");
       QString path2 = this->path;
       strcpy(comando,path2.replace(".disk", "_raid.disk").toStdString().c_str());
       FILE* d2 = fopen(comando, "r+b");
       MBR mbr;
       if(d1 != 0 && d2 != 0){
           fseek(d1,0,SEEK_SET);
           fread(&mbr, sizeof (MBR), 1, d1);
           int tamanoDisco = mbr.mbr_tamano - sizeof (MBR), primarias = 0, extendidas = 0;
           for(int i = 0; i < 4; i++){
               Partition particion = mbr.mbr_partition[i];
               if(particion.part_type == 'P' || particion.part_type == 'p') primarias++;
               else if(particion.part_type == 'E' || particion.part_type == 'e') extendidas++;
           }
           cout << "x ---------------------------- MBR --------------------------- x" << endl;
           cout << "   Tamano del disco : " << mbr.mbr_tamano << " bytes" << endl;
           cout << "   Fecha de creacion del disco : " << mbr.mbr_fecha_creacion << endl;
           cout << "   Firma del disco : " << mbr.mbr_signature << endl;
           cout << "   Ajuste del disco : " << mbr.disk_fit << endl;
           cout << "   Particiones primarias : " << primarias << endl;
           cout << "   Particiones Extendidas : " << extendidas << endl;
           cout << "x ------------------------------------------------------------ x" << endl;

           if(this->unit == "")this->unit = "K";
           if(this->type == "")this->type = "P";
           if(this->fit == "")this->fit = "WF";


           Partition nueva;
           if(this->size != 0 && accionEjecutada == 0){ //crear particion
               bool nombreIgual = false;
               int r = 0;
               while(r < 4 && !nombreIgual){
                   if(strcmp(mbr.mbr_partition[r].part_name,this->nombre.toStdString().c_str()) == 0)
                       nombreIgual = true;

                   r++;
               }

               if(!nombreIgual){
                   int tamano = this->size;
                   if(this->unit == "K")tamano = this->size * 1024;
                   else if(this->unit == "M")tamano = this->size * (1024*1024);

                   if(tamano < tamanoDisco){
                       if((primarias + extendidas) == 0){ // la primer particion
                           if(this->type.toUpper() == "P" || this->type.toUpper() == "E"){
                               mbr.mbr_partition[0].part_status = 'A';
                               mbr.mbr_partition[0].part_type = this->type.toStdString().c_str()[0];
                               mbr.mbr_partition[0].part_fit = this->fit.toUpper().toStdString().c_str()[0];
                               mbr.mbr_partition[0].part_size = tamano;
                               strcpy(mbr.mbr_partition[0].part_name,this->nombre.toStdString().c_str());
                               mbr.mbr_partition[0].part_start = sizeof (MBR);

                               nueva = mbr.mbr_partition[0];
                               fseek(d1,nueva.part_start,SEEK_SET);
                               fseek(d2,nueva.part_start,SEEK_SET);

                               int fin=(tamano/1024);
                               char buffer[1024];
                               for(int i=0;i<1024;i++){
                                   buffer[i]='1';
                               }

                               int j = 0;
                               while(j != fin){
                                   fwrite(&buffer,1024 , 1, d1);
                                   fwrite(&buffer, 1024, 1, d2);
                                   j++;
                               }

                               cout << " ::Particion " << nueva.part_type << " agregada exitosamente" << endl;

                           }else if(this->type.toUpper() == "L") cout << "error: no se pueden agregar particiones logicas sin una particion extendida" << endl;
                           accionEjecutada = 1;
                       }else if((primarias + extendidas) > 0 && (primarias + extendidas) < 4){ // ya hay una particion
                           if(this->type.toUpper() == "E" && extendidas == 1)cout << "error: no se puede crear otra particion extendida" << endl;
                           else{
                               int puntero = sizeof (MBR);
                               fseek(d1,puntero,SEEK_SET);
                               fseek(d2,puntero,SEEK_SET);
                               int p = 0;
                               char buffercon1[1024];
                               for(int i=0;i<1024;i++){
                                   buffercon1[i]='1';
                               }
                               QList<string> espaciosLibres = QList<string>();
                               int tamTmp = 0, fin = (tamanoDisco/1024);
                               while(p != fin){
                                   int byteActual = (p * 1024) + sizeof (MBR);
                                   char comp[1024];
                                   fread(&comp,1024,1,d1);
                                   if(strcmp(buffercon1,comp) == 1 || strcmp(buffercon1,comp) == 0){
                                       tamTmp = tamTmp + 1024;
                                   }

                                   if(p == (fin-1)){
                                       stringstream ss;
                                       ss << tamTmp;
                                       espaciosLibres.append(intToString(byteActual-tamTmp) + "." + ss.str());
                                       tamTmp = 0;
                                   }

                                   if(strcmp(buffercon1,comp) < 0){
                                       if(tamTmp != 0){
                                           stringstream ss;
                                           ss << tamTmp;
                                           espaciosLibres.append(intToString(byteActual-tamTmp) + "." + ss.str());
                                           tamTmp = 0;
                                       }
                                   }
                                   p++;
                               }

                               int byteInicio = 0;
                               if(mbr.disk_fit == 'F'){
                                   int j = 0;
                                   bool encontrado = false;
                                   while(!encontrado && j < espaciosLibres.length()){
                                       if(tamano <= QString::fromStdString(espaciosLibres.at(j)).split(".")[1].toInt()){
                                           byteInicio = QString::fromStdString(espaciosLibres.at(0)).split(".")[0].toInt();
                                           encontrado = true;
                                       }
                                       j++;
                                   }
                               }else{
                                   for(int i = 0; i < espaciosLibres.length(); i++){
                                       QStringList lista = QString::fromStdString(espaciosLibres.at(i)).split(".");
                                       int tamanoDisponible = lista[1].toInt();
                                       if(tamano <= tamanoDisponible){
                                           byteInicio = lista[0].toInt();
                                           int j = 0;
                                           bool encontrado = false;
                                           while (j < espaciosLibres.length() && !encontrado){
                                               if(tamano <= QString::fromStdString(espaciosLibres.at(j)).split(".")[1].toInt()){
                                                   if(mbr.disk_fit == 'B'){ // el mejor ajuste
                                                       if(QString::fromStdString(espaciosLibres.at(j)).split(".")[1].toInt() < tamanoDisponible){
                                                           byteInicio = QString::fromStdString(espaciosLibres.at(j)).split(".")[0].toInt();
                                                           encontrado = true;
                                                       }
                                                   }else if(mbr.disk_fit == 'W'){ // el peor ajuste
                                                       if(QString::fromStdString(espaciosLibres.at(j)).split(".")[1].toInt() > tamanoDisponible){
                                                           byteInicio = QString::fromStdString(espaciosLibres.at(j)).split(".")[0].toInt();
                                                           encontrado = true;
                                                       }
                                                   }
                                               }
                                               j++;
                                           }
                                       }
                                   }
                               }

                               if(byteInicio > 0){
                                   nueva.part_fit = this->fit.toUpper().toStdString().c_str()[0];
                                   strcpy(nueva.part_name,this->nombre.toStdString().c_str());
                                   nueva.part_size = tamano;
                                   nueva.part_type = this->type.toUpper().toStdString().c_str()[0];
                                   nueva.part_start = byteInicio;
                                   nueva.part_status = 'A';

                                   //escribirla en el mbr
                                   bool bandera = false;
                                   int k = 0;
                                   while(k < 4 && !bandera){
                                       if(mbr.mbr_partition[k].part_status == 'I'){
                                           mbr.mbr_partition[k] = nueva;
                                           bandera = true;
                                       }
                                       k++;
                                   }

                                   //la escribo en el disco
                                   fseek(d1,nueva.part_start,SEEK_SET);
                                   fseek(d2,nueva.part_start,SEEK_SET);

                                   int fin=(nueva.part_size/1024);
                                   char buffer[1024];
                                   for(int i=0;i<1024;i++){
                                       buffer[i]='1';
                                   }

                                   int j = 0;
                                   while(j != fin){
                                       fwrite(&buffer,1024 , 1, d1);
                                       fwrite(&buffer, 1024, 1, d2);
                                       j++;
                                   }

                                   accionEjecutada = 1;
                                   cout << " ::Particion " << nueva.part_name << " agregada con exito " << endl;
                               }else cout << "error: la particiones deseada no cabe en los espacios disponibles" << endl;
                           }
                       }else if(this->type.toUpper() == "L"){
                           if(extendidas == 0) cout << "error: no se puede crear la particion " << this->nombre.toStdString() << " sin una particion extendida" << endl;
                           else{
                               //creacion de particiones logicas
                               strcpy(nueva.part_name,this->nombre.toStdString().c_str());
                               cout << " ::Particion logica " << nueva.part_name << " creada con exito" << endl;
                               accionEjecutada = 1;
                           }
                       }else cout << "error: no se pueden agregar la particion " << this->nombre.toStdString() << " mas particiones " << endl;
                   }else cout << "error: no se puede agregar espacio mas grande que el disco " << endl;
               }else cout << "error: la particion " << this->nombre.toStdString() << " ya existe" << endl;
           }if(this->add != "" && accionEjecutada == 0){ //modificar particion
                int agregar_quitar = this->add.toInt(), c = 0, tamano = 0;
                bool listo = false, huboEspacio = false;
                while(c < 4 && !listo){
                    if(strcmp(mbr.mbr_partition[c].part_name,this->nombre.toStdString().c_str()) == 0){
                        tamano = agregar_quitar;
                        if(this->unit.toUpper() == "K") tamano = agregar_quitar * 1024;
                        else if(this->unit.toUpper() == "M") tamano = agregar_quitar * (1024 * 1024);
                        if(agregar_quitar > 0){ // se agrega mas espacio a una particion
                            if(c == 3){
                                if((tamano + mbr.mbr_partition[c].part_size + mbr.mbr_partition[c].part_start) <= mbr.mbr_tamano){
                                    mbr.mbr_partition[c].part_size = mbr.mbr_partition[c].part_size + tamano;

                                    fseek(d1,mbr.mbr_partition[c].part_start,SEEK_SET);
                                    fseek(d2,mbr.mbr_partition[c].part_start,SEEK_SET);
                                    int fin=(mbr.mbr_partition[c].part_size/1024);
                                    char buffer[1024];
                                    for(int i=0;i<1024;i++){
                                        buffer[i]='1';
                                    }

                                    int j = 0;
                                    while(j != fin){
                                        fwrite(&buffer,1024 , 1, d1);
                                        fwrite(&buffer, 1024, 1, d2);
                                        j++;
                                    }
                                    huboEspacio = true;
                                    listo = true;
                                }
                            }else{
                                if(mbr.mbr_partition[c+1].part_status == 'A'){
                                    if((tamano + mbr.mbr_partition[c].part_size + mbr.mbr_partition[c].part_start) <= mbr.mbr_partition[c+1].part_start){
                                        mbr.mbr_partition[c].part_size = mbr.mbr_partition[c].part_size + tamano;
                                        fseek(d1,mbr.mbr_partition[c].part_start,SEEK_SET);
                                        fseek(d2,mbr.mbr_partition[c].part_start,SEEK_SET);
                                        int fin=(mbr.mbr_partition[c].part_size/1024);
                                        char buffer[1024];
                                        for(int i=0;i<1024;i++){
                                            buffer[i]='1';
                                        }

                                        int j = 0;
                                        while(j != fin){
                                            fwrite(&buffer,1024 , 1, d1);
                                            fwrite(&buffer, 1024, 1, d2);
                                            j++;
                                        }
                                        huboEspacio = true;
                                        listo = true;
                                    }
                                }else{
                                    int h = c+1, ban = 0;
                                    while(h < 4 && !ban){
                                        if(h == 3){
                                            if((tamano + mbr.mbr_partition[c].part_size + mbr.mbr_partition[c].part_start) <= mbr.mbr_tamano){
                                                mbr.mbr_partition[c].part_size = mbr.mbr_partition[c].part_size + tamano;
                                                fseek(d1,mbr.mbr_partition[c].part_start,SEEK_SET);
                                                fseek(d2,mbr.mbr_partition[c].part_start,SEEK_SET);
                                                int fin=(mbr.mbr_partition[c].part_size/1024);
                                                char buffer[1024];
                                                for(int i=0;i<1024;i++){
                                                    buffer[i]='1';
                                                }

                                                int j = 0;
                                                while(j != fin){
                                                    fwrite(&buffer,1024 , 1, d1);
                                                    fwrite(&buffer, 1024, 1, d2);
                                                    j++;
                                                }
                                                huboEspacio = true;
                                                listo = true;
                                                ban = 1;
                                            }
                                        }else{
                                            if(mbr.mbr_partition[h].part_status == 'A'){
                                                if((tamano + mbr.mbr_partition[c].part_size + mbr.mbr_partition[c].part_start) <= mbr.mbr_partition[h].part_start){
                                                    mbr.mbr_partition[c].part_size = mbr.mbr_partition[c].part_size + tamano;
                                                    fseek(d1,mbr.mbr_partition[c].part_start,SEEK_SET);
                                                    fseek(d2,mbr.mbr_partition[c].part_start,SEEK_SET);
                                                    int fin=(mbr.mbr_partition[c].part_size/1024);
                                                    char buffer[1024];
                                                    for(int i=0;i<1024;i++){
                                                        buffer[i]='1';
                                                    }

                                                    int j = 0;
                                                    while(j != fin){
                                                        fwrite(&buffer,1024 , 1, d1);
                                                        fwrite(&buffer, 1024, 1, d2);
                                                        j++;
                                                    }
                                                    huboEspacio = true;
                                                    ban = 1;
                                                    listo = true;
                                                }
                                            }
                                        }
                                        h++;
                                    }
                                }
                            }
                        }else if(agregar_quitar < 0){ // se remueve espacio a una particion
                            if((tamano + mbr.mbr_partition[c].part_size) > 0){
                                mbr.mbr_partition[c].part_size = mbr.mbr_partition[c].part_size + tamano;
                                fseek(d1,mbr.mbr_partition[c].part_start,SEEK_SET);
                                fseek(d2,mbr.mbr_partition[c].part_start,SEEK_SET);
                                int fin=(mbr.mbr_partition[c].part_size/1024);
                                char buffer[1024];
                                for(int i=0;i<1024;i++){
                                    buffer[i]='1';
                                }

                                int j = 0;
                                while(j != fin){
                                    fwrite(&buffer,1024 , 1, d1);
                                    fwrite(&buffer, 1024, 1, d2);
                                    j++;
                                }
                                accionEjecutada = 1;
                                huboEspacio = 1;
                                listo = true;
                            }
                        }
                    }
                    c++;
                }
                if(!huboEspacio)cout << "error: ya no hay espacio para agregar / quitar en la particion " << this->nombre.toStdString() << endl;
                else{
                    accionEjecutada = 1;
                    cout << " ::Se modifico la particion " << this->nombre.toStdString() << " exitosamente" << endl;
                }
                if(!listo)cout << "error: la particion " << this->nombre.toStdString() << " no existe" << endl;
           }if(this->del != "" && accionEjecutada == 0){ // eliminar particion
                int g = 0;
                bool eliminada = false;
                while(g < 4 && !eliminada){
                    if(strcmp(mbr.mbr_partition[g].part_name, this->nombre.toStdString().c_str()) == 0){
                        string respuesta;
                        cout << " ::Seguro que desea eliminar la particion " << mbr.mbr_partition[g].part_name << "? [Y/n] " ;
                        getline(cin,respuesta);
                        if(respuesta == "n" || respuesta == "N")cout << " ::La particion " << mbr.mbr_partition[g].part_name << " no se ha eliminado" << endl;
                        else{

                            if(this->del.toUpper() == "FULL"){
                                int tamano = mbr.mbr_partition[g].part_size;
                                fseek(d1,mbr.mbr_partition[g].part_start,SEEK_SET);
                                fseek(d2,mbr.mbr_partition[g].part_start,SEEK_SET);
                                int fin=(tamano/1024);
                                char buffer[1024];
                                for(int i=0;i<1024;i++){
                                    buffer[i]='0';
                                }

                                int j = 0;
                                while(j != fin){
                                    fwrite(&buffer,1024 , 1, d1);
                                    fwrite(&buffer, 1024, 1, d2);
                                    j++;
                                }
                            }
                            nueva.part_fit = 'N';
                            strcpy(nueva.part_name, "N");
                            nueva.part_size = 0;
                            nueva.part_type = 'N';
                            nueva.part_start = -1;
                            nueva.part_status = 'I';
                            mbr.mbr_partition[g] = nueva;
                        }
                        eliminada = true;
                    }
                    g++;
                }
                if(!eliminada) cout << " ::La particion " << this->nombre.toStdString() << " no existe" << endl;
                accionEjecutada = 1;
           }

           fseek(d1,0,SEEK_SET);
           fwrite(&mbr, sizeof(MBR), 1, d1);//escribe mbr1
           fclose(d1);
           fseek(d2,0,SEEK_SET);
           fwrite(&mbr, sizeof(MBR), 1, d2);//escribe mbr2
           fclose(d2);

       }else{
           if(d1 != 0) fclose(d1);
           if(d2 != 0) fclose(d2);
           cout << "error: alguno de los discos no existe " << endl;
       }
    }

    if(accionEjecutada == 0) cout << "error: verificar parametros para 'fdisk'" << endl;
}

void Ejecutar::rep(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    if(parametrosObligatorios(6)){
        int posicionParticion = this->listaParticiones->buscarParticion("\0", "\0", this->id);
        if(posicionParticion < 0) cout << "error: la particion " << this->id.toStdString() << " no esta montada" << endl;
        else{
            if(this->path.split(".")[1].toUpper() == "JPG" || this->path.split(".")[1].toUpper() == "JPEG" || this->path.split(".")[1].toUpper() == "PNG" || this->path.split(".")[1].toUpper() == "TXT"){
                MBR mbr;
                char comando[500];
                QStringList arr = this->path.split("/");
                QString direccion = "";
                int i = 1;
                while (i < (arr.length()-1)){
                    direccion+= "/" + arr[i];
                    strcpy(comando, ("cd " + direccion).toStdString().c_str());
                    if(system(comando)){ //error
                        strcpy(comando, ("mkdir " + direccion).toStdString().c_str());
                        cout << " ::Creando " << direccion.toStdString() << " como directorio " << endl;
                        system(comando);
                    }
                    i++;
                }

                QString nombreimg = arr[arr.length()-1].split(".")[0];
                QString extension = arr[arr.length()-1].split(".")[1];
                QString texto = "digraph reporte{\n";
                QString pathDisco = this->listaParticiones->listaParticion.at(posicionParticion).path;
                Partition particion = this->listaParticiones->listaParticion.at(posicionParticion).particion;
                strcpy(comando, pathDisco.toStdString().c_str());
                FILE* f1= fopen(comando, "r+b");
                fseek(f1,0,SEEK_SET);// estableciendo puntero al inicio
                bool esunDot = true;
                if(f1 != 0){
                    if(this->nombre.toUpper() == "MBR"){
                        fread(&mbr, sizeof (MBR), 1, f1);
                        int tamanoDisco = mbr.mbr_tamano;
                        texto += "label=\"" + pathDisco + "\";\nnode [shape=box];\n";
                        texto += "mbr [label=<\n<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                        texto += "<TR><TD colspan=\"2\" bgcolor=\"darkolivegreen3\" >MBR</TD></TR>\n";
                        texto += "<TR><TD>mbr_tamano</TD><TD>" + QString::number(tamanoDisco) + "</TD></TR>\n";
                        texto += "<TR><TD>mbr_fecha_creacion</TD><TD>" + QString::fromStdString(mbr.mbr_fecha_creacion) + "</TD></TR>\n";
                        texto += "<TR><TD>mbr_disk_signature</TD><TD>" + QString::number(mbr.mbr_signature) + "</TD></TR>\n";
                        texto += "<TR><TD>disk_fit</TD><TD>" + QString(mbr.disk_fit) + "</TD></TR>\n";
                        for(int j = 0; j < 4; j++){
                            if(mbr.mbr_partition[j].part_status == 'A'){
                                texto += "<TR><TD>part_status_" + QString::number(j+1) + "</TD><TD>" + QString(mbr.mbr_partition[j].part_status) + "</TD></TR>\n";
                                texto += "<TR><TD>part_type_" + QString::number(j+1) + "</TD><TD>" + QString(mbr.mbr_partition[j].part_type) + "</TD></TR>\n";
                                texto += "<TR><TD>part_fit_" + QString::number(j+1) + "</TD><TD>" + QString(mbr.mbr_partition[j].part_fit) + "</TD></TR>\n";
                                texto += "<TR><TD>part_start_" + QString::number(j+1) + "</TD><TD>" + QString::number(mbr.mbr_partition[j].part_start) + "</TD></TR>\n";
                                texto += "<TR><TD>part_size_" + QString::number(j+1) + "</TD><TD>" + QString::number(mbr.mbr_partition[j].part_size) + "</TD></TR>\n";
                                texto += "<TR><TD>part_name_" + QString::number(j+1) + "</TD><TD>" + QString::fromStdString(mbr.mbr_partition[j].part_name) + "</TD></TR>\n";
                            }
                        }
                        texto += "</TABLE>>];\n}";
                    }else if(this->nombre.toUpper() == "DISK"){
                        fread(&mbr, sizeof (MBR), 1, f1);
                        int tamanoDisco = mbr.mbr_tamano;
                        int numNodo = 0;
                        texto +="graph [nodesep=0.01, rankdir=\"LR\", label=\"" + pathDisco + "\"];\n";
                        texto += "edge [color=white, arrowsize=.01, weight=.01, penwidth=.01];\n";
                        texto += "node [shape=record, height=1.25, style=filled];\n";
                        texto += QString::number(numNodo) + " [color=greenyellow, label=\"MBR\", width=.01];\n"; numNodo++;
                        for(int k = 0; k < 4; k++){
                            if(mbr.mbr_partition[k].part_status == 'A'){
                                double proporcion = (static_cast<double>(mbr.mbr_partition[k].part_size) / static_cast<double>(tamanoDisco)) * 100;
                                texto += QString::number(numNodo) + " [color=aquamarine2, label=\" "+ QString(mbr.mbr_partition[k].part_type) + "\\n";
                                texto += "(" + QString::fromStdString(mbr.mbr_partition[k].part_name) + ")\\n" + QString::number(proporcion) + "%\", ";
                                texto += "width=" + QString::number(proporcion*0.15) + "];\n" + QString::number(numNodo-1) + " -> " + QString::number(numNodo) + ";\n";
                                numNodo++;
                            }

                            if( k < 3){
                                if(mbr.mbr_partition[k].part_status == 'A' && mbr.mbr_partition[k + 1].part_status == 'I'){
                                    int tamano = 0, y = k;
                                    bool encontrada = false;
                                    while(!encontrada && y < 4){
                                        if(mbr.mbr_partition[y].part_status == 'A'){
                                            tamano = (mbr.mbr_partition[k].part_size + mbr.mbr_partition[k].part_start) - mbr.mbr_partition[y].part_start;
                                            double proporcion = (tamano / static_cast<double>(tamanoDisco)) * 100;
                                            texto += QString::number(numNodo) + " [color=lightsteelblue1, label=\" Espacio Libre\\n";
                                            texto += QString::number(proporcion) + "%\", ";
                                            texto += "width=" + QString::number(proporcion*0.15) + "];\n" + QString::number(numNodo-1) + " -> " + QString::number(numNodo) + ";\n";
                                            numNodo++;
                                            encontrada = true;
                                        }
                                        y++;
                                    }

                                    if(!encontrada){
                                        int diferencia = (( mbr.mbr_partition[k].part_start + mbr.mbr_partition[k].part_size) - tamanoDisco) * -1;
                                        if(diferencia > 1024){
                                            double proporcion = (diferencia / static_cast<double>(tamanoDisco)) * 100;
                                            texto += QString::number(numNodo) + " [color=lightsteelblue1, label=\" Espacio Libre\\n";
                                            texto += QString::number(proporcion) + "%\", ";
                                            texto += "width=" + QString::number(proporcion*0.15) + "];\n" + QString::number(numNodo-1) + " -> " + QString::number(numNodo) + ";\n";
                                            numNodo++;
                                        }
                                    }
                                }else if(mbr.mbr_partition[k].part_status == 'A' && mbr.mbr_partition[k + 1].part_status == 'A'){
                                    int diferencia = ( mbr.mbr_partition[k].part_start + mbr.mbr_partition[k].part_size) - mbr.mbr_partition[k + 1].part_start;
                                    if(diferencia > 1024){
                                        double proporcion = (diferencia / static_cast<double>(tamanoDisco)) * 100;
                                        texto += QString::number(numNodo) + " [color=lightsteelblue1, label=\" Espacio Libre\\n";
                                        texto += QString::number(proporcion) + "%\", ";
                                        texto += "width=" + QString::number(proporcion*0.15) + "];\n" + QString::number(numNodo-1) + " -> " + QString::number(numNodo) + ";\n";
                                        numNodo++;
                                    }
                                }else if(mbr.mbr_partition[0].part_status == 'I' && mbr.mbr_partition[k + 1].part_status == 'A'){

                                    int tamano = mbr.mbr_partition[k+1].part_start - sizeof (MBR);
                                    double proporcion = (tamano / static_cast<double>(tamanoDisco)) * 100;
                                    texto += QString::number(numNodo) + " [color=lightsteelblue1, label=\" Espacio Libre\\n";
                                    texto += QString::number(proporcion) + "%\", ";
                                    texto += "width=" + QString::number(proporcion*0.15) + "];\n" + QString::number(numNodo-1) + " -> " + QString::number(numNodo) + ";\n";
                                    numNodo++;
                                }
                            }if( k == 3 && mbr.mbr_partition[k].part_status == 'A'){
                                int diferencia = (( mbr.mbr_partition[k].part_start + mbr.mbr_partition[k].part_size) - tamanoDisco) * -1;
                                if(diferencia > 1024){
                                    double proporcion = (diferencia / static_cast<double>(tamanoDisco)) * 100;
                                    texto += QString::number(numNodo) + " [color=lightsteelblue1, label=\" Espacio Libre\\n";
                                    texto += QString::number(proporcion) + "%\", ";
                                    texto += "width=" + QString::number(proporcion*0.15) + "];\n" + QString::number(numNodo-1) + " -> " + QString::number(numNodo) + ";\n";
                                    numNodo++;
                                }
                            }
                        }
                        texto += "}";
                    }
                    else if(this->nombre.toUpper() == "INODE"){
                        fseek(f1,particion.part_start,SEEK_SET);
                        SuperBlock sb;
                        fread(&sb,sizeof (sb),1,f1);
                        texto += "label = \"" + this->id + "\";\nnode [shape=box];";
                        int inodos_ocupados = sb.s_inodes_count - sb.s_free_inodes_count, j = 0;
                        fseek(f1,sb.s_inode_start,SEEK_SET);
                        while( j != inodos_ocupados){
                            Inode inodo;
                            fread(&inodo,sizeof (Inode),1,f1);
                            if(inodo.i_uid > 0){
                                strcpy(inodo.i_atime,obtenerFecha().c_str());
                                texto += "I" + QString::number(inodo.i_id) + " [label=<<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                                texto += "<TR><TD colspan=\"2\" bgcolor=\"thistle2\">INODE_" + QString::number(inodo.i_id) + "</TD></TR>";
                                texto += "<TR><TD>i_uid</TD><TD>" + QString::number(inodo.i_uid) + "</TD></TR>\n";
                                texto += "<TR><TD>i_gid</TD><TD>" + QString::number(inodo.i_gid) + "</TD></TR>\n";
                                texto += "<TR><TD>i_size</TD><TD>" + QString::number(inodo.i_size) + "</TD></TR>\n";
                                texto += "<TR><TD>i_atime</TD><TD>" + QString::fromStdString(inodo.i_atime) + "</TD></TR>\n";
                                texto += "<TR><TD>i_mtime</TD><TD>" + QString::fromStdString(inodo.i_mtime) + "</TD></TR>\n";
                                for(int n = 0; n < 15; n++)
                                    texto += "<TR><TD>i_block_" + QString::number(n) + "</TD><TD>" + QString::number(inodo.i_block[n]) + "</TD></TR>\n";

                                texto += "<TR><TD>i_type</TD><TD>" + QString::number(inodo.i_type) + "</TD></TR>\n";
                                texto += "<TR><TD>i_perm</TD><TD>" + QString::number(inodo.i_perm) + "</TD></TR>\n";
                                texto += "</TABLE>>];\n";
                            }
                            j++;
                        }
                        texto += "}";
                    }else if(this->nombre.toUpper() == "JOURNALING"){
                        texto += "label = \"" + this->id + "\";\nnode [shape=box];\nb  [label=<" +
                                "<TABLE cellspacing=\"10\" cellpadding=\"10\">\n<TR><TD colspan=\"3\" bgcolor=\"darkolivegreen3\">" +
                                "JOURNALING</TD></TR>\n<TR><TD>Fecha y Hora</TD><TD>Usuario</TD><TD>Operacion</TD></TR>";
                        fseek(f1,particion.part_start,SEEK_SET);
                        SuperBlock sb;
                        fread(&sb,sizeof (sb),1,f1);
                        int j = 0, cantJournal = sb.s_journal_count;
                        fseek(f1,(particion.part_start + sizeof (SuperBlock)),SEEK_SET);
                        while (j != cantJournal){
                            Journal journal;
                            fread(&journal,sizeof (Journal),1,f1);
                            texto += "<TR><TD>" + QString::fromStdString(journal.j_fecha_hora) + "</TD><TD>" +
                                    QString::fromStdString(journal.j_user) + "</TD><TD>" +
                                    QString::fromStdString(journal.j_operation) + "</TD></TR>\n";
                            j++;
                        }
                        texto += "</TABLE>>];\n}";
                    }else if(this->nombre.toUpper() == "BLOCK"){
                        fseek(f1,particion.part_start,SEEK_SET);
                        SuperBlock sb;
                        fread(&sb,sizeof (sb),1,f1);
                        texto += "label = \"" + this->id + "\";\nnode [shape=box];\n";
                        int bloques_ocupados = sb.s_blocks_count - sb.s_free_block_count, j = 0;
                        fseek(f1,sb.s_block_start,SEEK_SET);
                        while( j != bloques_ocupados){
                            Bloque_Carpeta b_carpeta;
                            Bloque_Archivo b_archivo;
                            Bloque_Apuntador b_apuntador;
                            fread(&b_carpeta,block_size,1,f1);
                            if(b_carpeta.b_id > 0 && b_carpeta.b_id <= bloques_ocupados){
                                texto += "C" + QString::number(b_carpeta.b_id) + " [label=<<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                                texto += "<TR><TD colspan=\"3\" bgcolor=\"deepskyblue\">BLOQUE_CARPETA_" + QString::number(b_carpeta.b_id) + "</TD></TR>";
                                texto += "<TR><TD></TD><TD>NOMBRE</TD><TD>INODO</TD></TR>\n";
                                for(int t = 0; t < 4; t++){
                                    if(b_carpeta.b_content[t].b_inode > 0)
                                        texto += "<TR><TD>b_" + QString::number(t+1) + "</TD><TD>" + b_carpeta.b_content[t].b_name + "</TD><TD>" + QString::number(b_carpeta.b_content[t].b_inode) + "</TD></TR>\n";
                                    else
                                        texto += "<TR><TD>b_" + QString::number(t+1) + "</TD><TD> - </TD><TD>" + QString::number(b_carpeta.b_content[t].b_inode) + "</TD></TR>\n";
                                }
                                texto += "</TABLE>>];\n";
                            }
                            fread(&b_archivo,block_size,1,f1);
                            if(b_archivo.b_id > 0 && b_archivo.b_id <= bloques_ocupados){
                                texto += "A" + QString::number(b_archivo.b_id) + " [label=<<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                                texto += "<TR><TD bgcolor=\"lemonchiffon2\">BLOQUE_ARCHIVO_" + QString::number(b_archivo.b_id) + "</TD></TR>";
                                texto += "<TR><TD>" + QString::fromStdString(b_archivo.b_content) + "</TD></TR>\n";
                                texto += "</TABLE>>];\n";
                            }
                            fread(&b_apuntador,block_size,1,f1);
                            if(b_apuntador.b_id > 0 && b_apuntador.b_id <= bloques_ocupados){
                                texto += "AP" + QString::number(b_apuntador.b_id) + " [label=<<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                                texto += "<TR><TD colspan=\"2\" bgcolor=\"gold1\">BLOQUE_APUNTADOR_" + QString::number(b_apuntador.b_id) + "</TD></TR>";
                                texto += "<TR><TD></TD><TD>BLOQUE</TD></TR>\n";
                                for(int t = 0; t < 16; t++){
                                    if(b_apuntador.b_pointers[t] > 0)
                                        texto += "<TR><TD>b_" + QString::number(t+1) + "</TD><TD>" + QString::number(b_apuntador.b_pointers[t]) + "</TD></TR>\n";
                                    else
                                        texto += "<TR><TD>b_" + QString::number(t+1) + "</TD><TD>-1</TD></TR>\n";
                                }
                                texto += "</TABLE>>];\n";
                            }
                            j++;
                        }
                        texto += "}";
                    }else if(this->nombre.toUpper() == "BM_INODE"){
                        esunDot = false;
                        fseek(f1,particion.part_start,SEEK_SET);
                        SuperBlock sb;
                        fread(&sb,sizeof (sb),1,f1);
                        fseek(f1,sb.s_bm_inode_start,SEEK_SET);
                        char aux[sb.s_inodes_count];
                        fread(&aux,sb.s_inodes_count,1,f1);
                        texto = aux[0];
                        for(int i = 1; i < sb.s_inodes_count; i++){
                            if(i%20 == 0)texto += "\n";
                            else texto += aux[i];
                        }

                    }else if(this->nombre.toUpper() == "BM_BLOCK"){
                        esunDot = false;
                        texto = "";
                        fseek(f1,particion.part_start,SEEK_SET);
                        SuperBlock sb;
                        fread(&sb,sizeof (sb),1,f1);
                        fseek(f1,sb.s_bm_block_start,SEEK_SET);
                        char aux[sb.s_blocks_count];
                        fread(&aux,sb.s_blocks_count,1,f1);
                        texto = aux[0];
                        for(int i = 1; i < sb.s_blocks_count; i++){
                            if(i%20 == 0)texto += "\n";
                            else texto += aux[i];
                        }
                    }else if(this->nombre.toUpper() == "TREE"){
                        fseek(f1,particion.part_start,SEEK_SET);
                        SuperBlock sb;
                        fread(&sb,sizeof (sb),1,f1);
                        texto += "label = \"" + this->id + "\";\nrankdir=\"LR\";\nnode [shape=box];\n";
                        const int inodos_ocupados = (sb.s_inodes_count - sb.s_free_inodes_count);
                        int m = 0;
                        fseek(f1,sb.s_inode_start,SEEK_SET);
                        while( m != inodos_ocupados){
                            Inode inodo;
                            fread(&inodo,sizeof (Inode),1,f1);
                            if(inodo.i_id > 0 && inodo.i_id <= inodos_ocupados){
                                strcpy(inodo.i_atime,obtenerFecha().c_str());
                                texto += "I" + QString::number(inodo.i_id) + " [label=<<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                                texto += "<TR><TD colspan=\"2\" bgcolor=\"thistle2\">INODE_" + QString::number(inodo.i_id) + "</TD></TR>";
                                texto += "<TR><TD>i_uid</TD><TD>" + QString::number(inodo.i_uid) + "</TD></TR>\n";
                                texto += "<TR><TD>i_gid</TD><TD>" + QString::number(inodo.i_gid) + "</TD></TR>\n";
                                texto += "<TR><TD>i_size</TD><TD>" + QString::number(inodo.i_size) + "</TD></TR>\n";
                                texto += "<TR><TD>i_atime</TD><TD>" + QString::fromStdString(inodo.i_atime) + "</TD></TR>\n";
                                texto += "<TR><TD>i_mtime</TD><TD>" + QString::fromStdString(inodo.i_mtime) + "</TD></TR>\n";
                                for(int n = 0; n < 15; n++)
                                    texto += "<TR><TD>i_block_" + QString::number(n) + "</TD><TD>" + QString::number(inodo.i_block[n]) + "</TD></TR>\n";

                                texto += "<TR><TD>i_type</TD><TD>" + QString::number(inodo.i_type) + "</TD></TR>\n";
                                texto += "<TR><TD>i_perm</TD><TD>" + QString::number(inodo.i_perm) + "</TD></TR>\n";
                                texto += "</TABLE>>];\n";
                            }
                            m++;
                        }

                        const int bloques_ocupados = (sb.s_blocks_count - sb.s_free_block_count);
                        int j = 0;
                        fseek(f1,sb.s_block_start,SEEK_SET);
                        while( j != bloques_ocupados){
                            Bloque_Carpeta b_carpeta;
                            Bloque_Archivo b_archivo;
                            Bloque_Apuntador b_apuntador;
                            fread(&b_carpeta,block_size,1,f1);
                            if(b_carpeta.b_id > 0 && b_carpeta.b_id <= bloques_ocupados){
                                texto += "B" + QString::number(b_carpeta.b_id) + " [label=<<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                                texto += "<TR><TD colspan=\"3\" bgcolor=\"deepskyblue\">BLOQUE_CARPETA_" + QString::number(b_carpeta.b_id) + "</TD></TR>";
                                texto += "<TR><TD></TD><TD>NOMBRE</TD><TD>INODO</TD></TR>\n";
                                for(int t = 0; t < 4; t++){
                                    if(b_carpeta.b_content[t].b_inode > 0)
                                        texto += "<TR><TD>b_" + QString::number(t+1) + "</TD><TD>" + b_carpeta.b_content[t].b_name + "</TD><TD>" + QString::number(b_carpeta.b_content[t].b_inode) + "</TD></TR>\n";
                                    else
                                        texto += "<TR><TD>b_" + QString::number(t+1) + "</TD><TD> - </TD><TD>" + QString::number(b_carpeta.b_content[t].b_inode) + "</TD></TR>\n";
                                }
                                texto += "</TABLE>>];\n";
                            }
                            fread(&b_archivo,block_size,1,f1);
                            if(b_archivo.b_id > 0 && b_archivo.b_id <= bloques_ocupados){
                                texto += "B" + QString::number(b_archivo.b_id) + " [label=<<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                                texto += "<TR><TD bgcolor=\"lemonchiffon2\">BLOQUE_ARCHIVO_" + QString::number(b_archivo.b_id) + "</TD></TR>";
                                texto += "<TR><TD>" + QString::fromStdString(b_archivo.b_content) + "</TD></TR>\n";
                                texto += "</TABLE>>];\n";
                            }
                            fread(&b_apuntador,block_size,1,f1);
                            if(b_apuntador.b_id > 0 && b_apuntador.b_id <= bloques_ocupados){
                                texto += "B" + QString::number(b_apuntador.b_id) + " [label=<<TABLE cellspacing=\"10\" cellpadding=\"10\">\n";
                                texto += "<TR><TD colspan=\"2\" bgcolor=\"gold1\">BLOQUE_APUNTADOR_" + QString::number(b_apuntador.b_id) + "</TD></TR>";
                                texto += "<TR><TD></TD><TD>BLOQUE</TD></TR>\n";
                                for(int t = 0; t < 16; t++){
                                    if(b_apuntador.b_pointers[t] > 0)
                                        texto += "<TR><TD>b_" + QString::number(t+1) + "</TD><TD>" + QString::number(b_apuntador.b_pointers[t]) + "</TD></TR>\n";
                                    else
                                        texto += "<TR><TD>b_" + QString::number(t+1) + "</TD><TD>-1</TD></TR>\n";
                                }
                                texto += "</TABLE>>];\n";
                            }
                            j++;
                        }
                        m = 0;
                        fseek(f1,sb.s_inode_start,SEEK_SET);
                        while( m != inodos_ocupados){
                            Inode inodo;
                            fread(&inodo,sizeof (Inode),1,f1);
                            if(inodo.i_id > 0 && inodo.i_id <= inodos_ocupados){
                                for(int n = 0; n < 15; n++){
                                    if(inodo.i_block[n] > 0)
                                        texto += "I" + QString::number(inodo.i_id) + " -> B" + QString::number(inodo.i_block[n]) +";\n";
                                }
                            }
                            m++;
                        }

                        j = 0;
                        fseek(f1,sb.s_block_start,SEEK_SET);
                        while( j != bloques_ocupados){
                            Bloque_Carpeta b_carpeta;
                            fread(&b_carpeta,block_size,1,f1);
                            if(b_carpeta.b_id > 0 && b_carpeta.b_id <= bloques_ocupados){
                                for(int t = 0; t < 4; t++){
                                    if(b_carpeta.b_content[t].b_inode > 0 && b_carpeta.b_content[t].b_inode <= bloques_ocupados)
                                        texto += "B" + QString::number(b_carpeta.b_id) + " -> I" + QString::number(b_carpeta.b_content[t].b_inode) + ";\n";
                                }
                            }

                            Bloque_Apuntador b_apuntador;
                            fread(&b_apuntador,block_size,1,f1);
                            if(b_apuntador.b_id > 0 && b_apuntador.b_id <= bloques_ocupados){
                                for(int t = 0; t < 16; t++){
                                    if(b_apuntador.b_pointers[t] > 0 && b_apuntador.b_pointers[t] <= bloques_ocupados)
                                        texto += "B" + QString::number(b_apuntador.b_id) + " -> B" + QString::number(b_apuntador.b_pointers[t]) + ";\n";
                                }
                            }
                            j++;
                        }

                        texto += "}";
                    }else if(this->nombre.toUpper() == "SB"){
                        texto += "label = \"" + this->id + "\";\nnode [shape=box];\nb  [label=<" +
                                "<TABLE cellspacing=\"10\" cellpadding=\"10\">\n<TR><TD colspan=\"2\" bgcolor=\"darkolivegreen3\">" +
                                "SUPER BLOQUE</TD></TR>\n";
                        SuperBlock SB;
                        fseek(f1,particion.part_start,SEEK_SET);
                        fread(&SB,sizeof (SuperBlock),1,f1);
                        texto += "<TR><TD>s_filesystem_type</TD><TD>3</TD></TR>\n";
                        texto += "<TR><TD>s_inodes_count</TD><TD>" + QString::number(SB.s_inodes_count) + "</TD></TR>\n";
                        texto += "<TR><TD>s_blocks_count</TD><TD>" + QString::number(SB.s_blocks_count) + "</TD></TR>\n";
                        texto += "<TR><TD>s_free_inodes_count</TD><TD>" + QString::number(SB.s_free_inodes_count) + "</TD></TR>\n";
                        texto += "<TR><TD>s_free_block_count</TD><TD>" + QString::number(SB.s_free_block_count) + "</TD></TR>\n";
                        texto += "<TR><TD>s_mtime</TD><TD>" + QString::fromStdString(SB.s_mtime) + "</TD></TR>\n";
                        texto += "<TR><TD>s_umtime</TD><TD>" + QString::fromStdString(SB.s_umtime) + "</TD></TR>\n";
                        texto += "<TR><TD>s_mnt_count</TD><TD>" + QString::number(SB.s_mnt_count) + "</TD></TR>\n";
                        texto += "<TR><TD>s_magic</TD><TD>0xEF53</TD></TR>\n";
                        texto += "<TR><TD>s_bm_inode_start</TD><TD>" + QString::number(SB.s_bm_inode_start) + "</TD></TR>\n";
                        texto += "<TR><TD>s_bm_block_start</TD><TD>" + QString::number(SB.s_bm_block_start) + "</TD></TR>\n";
                        texto += "<TR><TD>s_inode_start</TD><TD>" + QString::number(SB.s_inode_start) + "</TD></TR>\n";
                        texto += "<TR><TD>s_block_start</TD><TD>" + QString::number(SB.s_block_start) + "</TD></TR>\n";
                        texto += "<TR><TD>s_inode_size</TD><TD>" + QString::number(SB.s_inode_size) + "</TD></TR>\n";
                        texto += "<TR><TD>s_block_size</TD><TD>" + QString::number(SB.s_block_size) + "</TD></TR>\n";
                        texto += "<TR><TD>s_first_ino</TD><TD>" + QString::number(SB.s_first_ino) + "</TD></TR>\n";
                        texto += "<TR><TD>s_first_blo</TD><TD>" + QString::number(SB.s_first_blo) + "</TD></TR>\n";
                        texto += "</TABLE>>];\n}";
                    }else if(this->nombre.toUpper() == "FILE"){
                        if(this->ruta != "" && this->ruta.contains(".")){
                            //reporte
                            texto +="}";
                        }else cout << "error: reporte 'file' debe tener la ruta del archivo a mostrar" << endl;
                    }else if(this->nombre.toUpper() == "LS"){

                    }


                    fclose(f1);

                    ofstream archivo;
                    if(esunDot){
                        archivo.open(direccion.toStdString() + "/" + nombreimg.toStdString() + ".dot");
                        archivo << texto.toStdString() << endl;
                        archivo.close();

                        QString cmd = "cd " + direccion + " && dot -T" + extension + " " + nombreimg + ".dot -o " + nombreimg + "." + extension;
                        strcpy(comando,cmd.toStdString().c_str());
                        system(comando);
                    }else{
                        archivo.open(direccion.toStdString() + "/" + nombreimg.toStdString() + ".txt");
                        archivo << texto.toStdString() << endl;
                        archivo.close();
                    }
                }else cout << "error: el disco no existe" << endl;

            }else cout << "error: la extension para la creacion del reporte es incorrecta " << endl;
        }
    }
}

void Ejecutar::mount(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    if(parametrosObligatorios(4)){
        char comando[256];
        strcpy(comando, this->path.toStdString().c_str());
        MBR mbr;
        FILE* d1 = fopen(comando, "r+b");
        if(d1 != 0){
            fseek(d1,0,SEEK_SET);
            fread(&mbr, sizeof (MBR), 1, d1);
            bool encontrado = false;
            int i = 0;
            char nombre[16];
            strcpy(nombre, this->nombre.toStdString().c_str());
            while(i < 4 && !encontrado){
                if(strcmp(nombre, mbr.mbr_partition[i].part_name) == 0){
                    Particion part = Particion(this->path, this->nombre, mbr.mbr_partition[i]);
                    part.Fecha = obtenerFecha();
                    this->listaParticiones->agregarParticion(part);
                    encontrado = true;
                }
                i++;
            }
            if(!encontrado) cout << "error: la particion " << this->nombre.toStdString() << " no existe" << endl;
        }else cout << "error: el disco solicitado no existe" << endl;
        fclose(d1);
    }
}

void Ejecutar::unmount(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    if(parametrosObligatorios(9))this->listaParticiones->quitarParticion(this->id,obtenerFecha());
}

void Ejecutar::login(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    if(parametrosObligatorios(10)){
        if(usuario->hayUsuario)cout << "error: primero debe cerrar sesion de " << usuario->nombre << endl;
        else{
            Particion particion = this->listaParticiones->devolverParticion(this->id);
            if(particion.name == "NULL")cout << "error: la particion " << this->id.toStdString() << " no esta montada" << endl;
            else{
                char char256[256];
                strcpy(char256,particion.path.toStdString().c_str());
                FILE* disco = fopen(char256,"r+b");
                if(disco != 0){
                    SuperBlock SB;
                    Inode inodo;
                    fseek(disco,particion.particion.part_start,SEEK_SET);
                    fread(&SB,sizeof (SB),1,disco);
                    fseek(disco,(SB.s_inode_start + inode_size),SEEK_SET);
                    fread(&inodo,inode_size,1,disco);
                    QString contenido = "";
                    for(int i = 0; i < 15; i++){
                        if(inodo.i_block[i] > 0 && inodo.i_block[i] <= abs(SB.s_blocks_count - SB.s_free_block_count)){
                            Bloque_Archivo archivo;
                            fseek(disco,(SB.s_block_start + ((inodo.i_block[i] - 1) * block_size)),SEEK_SET);
                            fread(&archivo,block_size,1,disco);
                            contenido += QString::fromStdString(archivo.b_content);
                        }
                    }

                    QStringList linea = contenido.split('\n');
                    int j = 0, encontrado = 0;
                    while(j < (linea.length() - 1) && !encontrado){
                        QStringList individual = linea[j].split(',');
                        if(individual[1].toUpper() == "U"){
                            if(individual[3] == this->usr && individual[4] == this->pwd){
                                strcpy(this->usuario->grupo,individual[2].toStdString().c_str());
                                strcpy(this->usuario->nombre, this->usr.toStdString().c_str());
                                strcpy(this->usuario->passwd, this->pwd.toStdString().c_str());
                                this->usuario->hayUsuario = true;
                                this->usuario->particion = particion;
                                cout << " ::Acceso a " << this->usr.toStdString() << " concedido " << endl;
                                encontrado = 1;
                            }
                        }
                        j++;
                    }

                    if(!encontrado)cout << "error: acceso a usuario '" << this->usr.toStdString() << "' denegado, verificar credenciales" << endl;
                    fclose(disco);
                }else cout << "error: el disco " << char256 << " no existe" << endl;
            }
        }
    }
}

void Ejecutar::logout(){
    if(this->usuario->hayUsuario){
        cout << " ::Sesion de " << this->usuario->nombre << " cerrada" << endl;
        this->usuario = new Usuario();
    }else cout << "error: no hay usuario activo" << endl;
}

void Ejecutar::mkfs(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    if(parametrosObligatorios(9)){
        Particion particion = this->listaParticiones->devolverParticion(this->id);
        if(particion.name == "NULL")cout << "error: la particion " << this->id.toStdString() << " no esta montada" << endl;
        else{
            char char256[256];
            strcpy(char256,particion.path.toStdString().c_str());
            FILE* disco = fopen(char256,"r+b");
            if(disco != 0){
                fseek(disco,particion.particion.part_start,SEEK_SET);
                int fin=(particion.particion.part_size/1024);
                char buffer[1024];
                int i=0;
                for(i=0;i<1024;i++){
                    buffer[i]='0';
                }

                int j = 0;
                while(j != fin){
                    fwrite(&buffer,1024 , 1, disco);
                    j++;
                }

                //calculo el numero de bloques
                const double n = (particion.particion.part_size - sizeof (SuperBlock)) / (sizeof (Journal) + 4 + inode_size + (3 * block_size));
                const int numero_bloques = floor(n);

                SuperBlock SB;
                SB.s_filesystem_type = 3;
                SB.s_inodes_count = numero_bloques;
                SB.s_blocks_count = 3 * numero_bloques;
                SB.s_free_block_count = (3 * numero_bloques) - 2;
                SB.s_free_inodes_count = numero_bloques - 2;
                strcpy(SB.s_mtime,particion.Fecha.c_str());
                strcpy(SB.s_umtime,this->listaParticiones->fechaUnmount.c_str());
                SB.s_inode_start = particion.particion.part_start + sizeof (SuperBlock) + (numero_bloques * sizeof (Journal)) + numero_bloques + (3 * numero_bloques);
                SB.s_block_start = SB.s_inode_start + (numero_bloques * inode_size);
                SB.s_magic = magic_number;
                SB.s_inode_size = inode_size;
                SB.s_block_size = block_size;
                SB.s_first_ino = SB.s_inode_start + (2 * inode_size);
                SB.s_first_blo = SB.s_block_start + (2 * block_size);
                SB.s_bm_inode_start = particion.particion.part_start + sizeof (SuperBlock) + (numero_bloques * sizeof (Journal));
                SB.s_bm_block_start = SB.s_bm_inode_start + numero_bloques;
                SB.s_journal_count = 3;

                Journal primerJournal;
                strcpy(primerJournal.j_user,"root");
                strcpy(primerJournal.j_fecha_hora,obtenerFecha().c_str());
                string primerOperacion = "mkfs -id=" + this->id.toStdString();
                if(this->type != "")primerOperacion += " -type=" + this->type.toStdString();
                strcpy(primerJournal.j_operation,primerOperacion.c_str());
                fseek(disco,(particion.particion.part_start + sizeof (SuperBlock)),SEEK_SET);
                fwrite(&primerJournal,sizeof (Journal),1,disco);


                //escribir el super bloque al inicio de la particion
                fseek(disco,particion.particion.part_start,SEEK_SET);
                fwrite(&SB,sizeof (SuperBlock),1,disco);

                //archivo users.txt
                string contenido = "1,G,root\n1,U,root,root,123\n";
                //marcar los primeros bitmap
                fseek(disco,SB.s_bm_inode_start,SEEK_SET);
                fwrite(&unUno,1,1,disco);
                fseek(disco,SB.s_bm_block_start,SEEK_SET);
                fwrite(&unUno,1,1,disco);
                fseek(disco,SB.s_bm_inode_start + 1,SEEK_SET);
                fwrite(&unUno,1,1,disco);
                fseek(disco,SB.s_bm_block_start + 1,SEEK_SET);
                fwrite(&unUno,1,1,disco);
                //primer inodo y primer bloque de archivos para /
                Inode inodo;
                inodo.i_id = 1;
                inodo.i_uid = 1;
                inodo.i_gid = 1;
                inodo.i_size = 0;
                strcpy(inodo.i_atime,obtenerFecha().c_str());
                strcpy(inodo.i_mtime,obtenerFecha().c_str());
                inodo.i_block[0] = 1;
                for(int g = 1; g < 15; g++)
                    inodo.i_block[g] = -1;

                inodo.i_type = 1;
                inodo.i_perm = 777;
                fseek(disco,SB.s_inode_start,SEEK_SET);
                fwrite(&inodo,sizeof (Inode),1,disco);
                Bloque_Carpeta bloque;
                bloque.b_id = 1;
                strcpy(bloque.b_content[0].b_name,"/");
                bloque.b_content[0].b_inode = 2;
                for(int h = 1; h < 4; h++)
                    bloque.b_content[h].b_inode = -1;

                fseek(disco,SB.s_block_start,SEEK_SET);
                fwrite(&bloque,block_size,1,disco);

                strcpy(primerJournal.j_fecha_hora,obtenerFecha().c_str());
                strcpy(primerJournal.j_operation,"mkdir -path=/");
                fseek(disco,(particion.particion.part_start + sizeof (SuperBlock) + sizeof (Journal)),SEEK_SET);
                fwrite(&primerJournal,sizeof (Journal),1,disco);

                //ahora para el archivo users.txt
                inodo.i_id = 2;
                inodo.i_size = contenido.length();
                strcpy(inodo.i_atime,obtenerFecha().c_str());
                strcpy(inodo.i_mtime,obtenerFecha().c_str());
                inodo.i_block[0] = 2;
                for(int g = 1; g < 15; g++)
                    inodo.i_block[g] = -1;

                inodo.i_type = 0;
                fseek(disco,(SB.s_inode_start + inode_size),SEEK_SET);
                fwrite(&inodo,sizeof (Inode),1,disco);
                Bloque_Archivo bloqueArchivo;
                bloqueArchivo.b_id = 2;
                strcpy(bloqueArchivo.b_content,contenido.c_str());
                fseek(disco,(SB.s_block_start + block_size),SEEK_SET);
                fwrite(&bloqueArchivo,block_size,1,disco);

                strcpy(primerJournal.j_fecha_hora,obtenerFecha().c_str());
                strcpy(primerJournal.j_operation,"mkfile -path=/users.txt -size=27");
                fseek(disco,(particion.particion.part_start + sizeof (SuperBlock) + ( 2 * sizeof (Journal))),SEEK_SET);
                fwrite(&primerJournal,sizeof (Journal),1,disco);


                fclose(disco);
                cout << " ::Particion " << this->id.toStdString() << " formateada" << endl;


            }else cout << "error: el disco " << char256 << " no existe" << endl;
        }
    }
}

void Ejecutar::mkgrp(Nodo *raiz){
    this->limpiarVariables();
    for(int i = 0; i < raiz->hijos.length(); i++){
        Nodo p = raiz->hijos.at(i); //envio el nodo del parametro unitario (size, path, name, etc)
        colocarParametros(&p);
    }

    if(parametrosObligatorios(11)){
        if(this->usuario->hayUsuario){
            if(!strcmp(this->usuario->nombre,"root")){
                QString restante = "";
                Particion particion = this->usuario->particion;
                char char256[256];
                strcpy(char256,particion.path.toStdString().c_str());
                FILE* disco = fopen(char256,"r+b");
                if(disco != 0){
                    SuperBlock SB;
                    Inode inodo;
                    fseek(disco,particion.particion.part_start,SEEK_SET);
                    fread(&SB,sizeof (SB),1,disco);
                    fseek(disco,(SB.s_inode_start + inode_size),SEEK_SET);
                    fread(&inodo,inode_size,1,disco);
                    QString contenido = "";
                    for(int i = 0; i < 15; i++){
                        if(inodo.i_block[i] > 0 && inodo.i_block[i] <= abs(SB.s_blocks_count - SB.s_free_block_count)){
                            Bloque_Archivo archivo;
                            fseek(disco,(SB.s_block_start + ((inodo.i_block[i] - 1) * block_size)),SEEK_SET);
                            fread(&archivo,block_size,1,disco);
                            contenido += QString::fromStdString(archivo.b_content);
                        }
                    }
                    QString aux = contenido;
                    QStringList linea = contenido.split('\n');
                    int j = 0, encontrado = 0, id_colocar = 0;
                    while(j < (linea.length() - 1) && !encontrado){
                        QStringList individual = linea[j].split(',');
                        if(individual[1].toUpper() == "G"){
                            if(individual[2] == this->nombre)encontrado = 1;
                            id_colocar = individual[0].toInt();
                        }
                        j++;
                    }

                    if(encontrado)cout << "error: el " << this->nombre.toStdString() << " ya existe" << endl;
                    else{
                        id_colocar++;
                        QString a_agregar = QString::number(id_colocar) + ",G," + this->nombre + "\n";
                        fseek(disco,(SB.s_inode_start + inode_size),SEEK_SET);
                        fread(&inodo,inode_size,1,disco);
                        int i = 0, ejecutado = 0;
                        while(i < 15 && !ejecutado){
                            if(inodo.i_block[i] > 0 && inodo.i_block[i] <= abs(SB.s_blocks_count - SB.s_free_block_count)){
                                Bloque_Archivo archivo;
                                fseek(disco,(SB.s_block_start + ((inodo.i_block[i] - 1) * block_size)),SEEK_SET);
                                fread(&archivo,block_size,1,disco);
                                if(strlen(archivo.b_content) <= 64){
                                    int caracteresdisponibles = 64 - strlen(archivo.b_content);
                                    if(a_agregar.length() <= caracteresdisponibles){
                                        aux += a_agregar;
                                        ejecutado = 1;
                                    }else{
                                        aux += (a_agregar.left(caracteresdisponibles));
                                        restante = a_agregar.replace(a_agregar.left(caracteresdisponibles), "");
                                    }
                                    strcpy(archivo.b_content,aux.toStdString().c_str());
                                    inodo.i_size = strlen(archivo.b_content);
                                    fseek(disco,(SB.s_block_start + ((inodo.i_block[i] - 1) * block_size)),SEEK_SET);
                                    fwrite(&archivo,block_size,1,disco);
                                }
                            }else if(inodo.i_block[i] == -1){ //inactivo
                                if(restante.length() > 0){
                                    int bloqueSig = SB.s_blocks_count - SB.s_free_block_count + 1, g = 0, flag = 0;
                                    fseek(disco,SB.s_bm_block_start,SEEK_SET);
                                    while(g < SB.s_blocks_count && !flag){
                                        char kk;
                                        fread(&kk,1,1,disco);
                                        if(kk == '0'){
                                            flag = 1;
                                            fwrite(&unUno,1,1,disco);
                                            SB.s_free_block_count = SB.s_free_block_count - 1;
                                        }
                                        g++;
                                    }
                                    if(flag){
                                        inodo.i_block[i] = bloqueSig;
                                        Bloque_Archivo arrrrchivo;
                                        arrrrchivo.b_id = bloqueSig;
                                        if(restante.length() <= 64){
                                            strcpy(arrrrchivo.b_content,restante.toStdString().c_str());
                                            ejecutado = 1;
                                        }else{
                                            strcpy(arrrrchivo.b_content,restante.left(64).toStdString().c_str());
                                            restante = restante.replace(restante.left(64), "");
                                        }
                                        fseek(disco,(SB.s_block_start + ((inodo.i_block[i] - 1) * block_size)),SEEK_SET);
                                        fwrite(&arrrrchivo,block_size,1,disco);
                                    }else cout << "error: ya no hay espacio para mas bloques " << endl;
                                }
                            }
                            fseek(disco,(SB.s_inode_start + inode_size),SEEK_SET);
                            fwrite(&inodo,inode_size,1,disco);
                            i++;
                        }
                        fseek(disco,(SB.s_inode_start + inode_size),SEEK_SET);
                        fwrite(&inodo,inode_size,1,disco);
                    }
                    fseek(disco,particion.particion.part_start,SEEK_SET);
                    fwrite(&SB,sizeof (SB),1,disco);
                    fclose(disco);
                }
            }else cout << "error: el comando mkgrp solo lo puede ejecutar el usuario 'root'" << endl;
        }else cout << "error: debe iniciar sesion de primero " << endl;
    }
}

void Ejecutar::pause(){
    string respuesta;
    cout << " ::Presione cualquier tecla para continuar " ;
    getline(cin, respuesta);
}

bool Ejecutar::parametrosObligatorios(int comando){
    if(this->parametrosCorrectos(comando))return true;
    else{
        cout << "error: verifique parametros, hace(n) falta uno(s)" << endl;
        return false;
    }
}

bool Ejecutar::parametrosCorrectos(int comando){ //parametros obligatorios
    if(comando == 1 && this->size != 0 && this->path != "")return true;
    else if(comando == 8 && this->path != "")return true;
    else if(comando == 4 && this->path != "" && this->nombre != "") return true;
    else if(comando == 6 && this->nombre != "" && this->path != "" && this->id != ""){
        if(reporteValido(this->nombre.toUpper()))return true;
        else cout << "error: el reporte de " << this->nombre.toStdString() << " no existe" << endl;
    }else if(comando == 9 && this->id != "") return true;
    else if(comando == 10 && this->usr != "" && this->pwd != "" && this->id != "")return true;
    else if(comando == 11 && this->nombre != "" && this->nombre.length() <= 10)return true;
    else if(comando == 12 && this->usr != "" && this->pwd != "" && this->grp != "")return true;
    else if(comando == 13 && this->usr != "")return true;
    else if(comando == 14 && this->path != "" && this->ugo != "")return true;
    else if(comando == 15 && this->fileParam != "")return true;
    else if(comando == 16 && this->path != "" && this->cont != "")return true;
    else if(comando == 17 && this->path != "" && this->dest != "")return true;
    else if(comando == 18 && this->usr != "" && this->path != "")return true;
    else if(comando == 19 && this->usr != "" && this->grp != "")return true;
    return false;
}

bool Ejecutar::reporteValido(QString nombre){
    QStringList lista = {"MBR", "DISK", "INODE", "JOURNALING", "BLOCK", "BM_INODE", "BM_BLOCK", "TREE", "SB", "FILE", "LS"};
    for(int i = 0; i < lista.length(); i++){
        if(nombre == lista.at(i))return true;
    }

    return false;
}

void Ejecutar::colocarParametros(Nodo *raiz){
    QString v = raiz->hijos.at(0).valor;
    QString &valor = v.replace("\"", "").replace(" ", "");
    switch (raiz->tipo) {
        case 1: // size
            {
                if(raiz->hijos.at(0).tipo == 23){
                    long tamano = valor.toLong();
                    if(tamano > 0) this->size = valor.toLong();
                    else cout << "error: El tamano " << valor.toStdString() << " no es valido, tiene que ser mayor a cero" << endl;
                }
                else cout << "error: El tamano " << valor.toStdString() << " no es valido" << endl;
            }
            break;
        case 2: // fit
            {
                if(valor.toUpper() == "BF" || valor.toUpper() == "FF" || valor.toUpper() == "WF") this->fit = valor;
                else cout << "error: El ajuste " << valor.toStdString() << " no es valido" << endl;
            }
            break;
        case 3: // unit
            {
                if(valor.toUpper() == "K" || valor.toUpper() == "M" || valor.toUpper() == "B") this->unit = valor;
                else cout << "error: La unidad " << valor.toStdString() << " no es valida" << endl;
            }
            break;
        case 4: // path
            {
                if(valor.contains('/') || valor.contains('.')) this->path = valor;
                else cout << "error: Verificar el directorio " << valor.toStdString() << endl;
            }
            break;
        case 7: // type
            {
                if(valor.toUpper() == "P" || valor.toUpper() == "E" || valor.toUpper() == "L" ||
                        valor.toUpper() == "FAST" || valor.toUpper() == "FULL") this->type = valor;
                else cout << "error: El tipo " << valor.toStdString() << " no es valido" << endl;
            }
            break;
        case 8: // add
            {
                if(raiz->hijos.at(0).tipo == 23)this->add = valor;
                else cout << "error: " << valor.toStdString() << " no es valido para el parametro 'add'" << endl;
            }
            break;
        case 9: // delete
            {
                if(valor.toUpper() == "FAST" || valor.toUpper() == "FULL")this->del = valor;
                else cout << "error: El valor " << valor.toStdString() << " no es valido para 'delete'" << endl;
            }
            break;
        case 10: // name
            {
                if(raiz->hijos.at(0).tipo == 24 || raiz->hijos.at(0).tipo == 26) this->nombre = valor;
                else cout << "error: Se espera un identificador o mbr/disk para 'name'" << endl;
                if(this->nombre.length() > 16){
                    this->nombre = "";
                    cout << "error: el nombre de la particion no debe ser mayor a 16 caracteres" << endl;
                }
            }
            break;
        case 13: // id
            {
                if(raiz->hijos.at(0).tipo == 24 || raiz->hijos.at(0).tipo == 26) this->id = valor;
                else cout << "error: se espera un identificador para 'id'" << endl;
            }
            break;
        case 55: //usr
        {
            if(valor.length() <= 10){
                if(raiz->hijos.at(0).tipo == 24 || raiz->hijos.at(0).tipo == 26) this->usr = valor;
                else cout << "error: se espera un identificador para 'usr'" << endl;
            }else cout << "error: el tamano del nombre del usuario no puede ser mayor a diez" << endl;
        }
            break;
        case 56: //pwd
        {
            if(valor.length() <= 10)this->pwd = valor;
            else cout << "error: el tamano de la contrasena no puede ser mayor a diez" << endl;
        }
            break;
        case 57: //grp
        {
            if(valor.length() <= 10){
                if(raiz->hijos.at(0).tipo == 24 || raiz->hijos.at(0).tipo == 26) this->grp = valor;
                else cout << "error: se espera un identificador para 'grp'" << endl;
            }else cout << "error: el tamano del nombre del grupo no puede ser mayor a diez" << endl;
        }
            break;
        case 58: // ugo
        {
            if(raiz->hijos.at(0).tipo == 53) this->ugo = valor;
            else cout << "error: valor invalido para 'ugo'" << endl;
        }
            break;
        case 59: //cont
        {
            if(valor.contains('/') || valor.contains('.')) this->cont = valor;
            else cout << "error: Verificar el directorio " << valor.toStdString() << endl;
        }
            break;
        case 60: // file
        {
            if(valor.contains('/') || valor.contains('.')) this->fileParam = valor;
            else cout << "error: Verificar el directorio " << valor.toStdString() << endl;
        }
            break;
        case 61: // dest
        {
            if(valor.contains('/') || valor.contains('.')) this->dest = valor;
            else cout << "error: Verificar el directorio " << valor.toStdString() << endl;
        }
            break;
        case 62: // ruta
        {
            if(valor.contains('/') || valor.contains('.')) this->ruta = valor;
            else cout << "error: Verificar el directorio " << valor.toStdString() << endl;
        }
            break;
        default:
            cout << "error: Parametro desconocido " << endl;
    }
}

void Ejecutar::limpiarVariables(){
    this->size = 0;
    this->nombre = "";
    this->unit = "";
    this->type = "";
    this->path = "";
    this->fit = "";
    this->del = "";
    this->add = "";
    this->id = "";
    this->usr = "";
    this->pwd = "";
    this->grp = "";
    this->ugo = "";
    this->R = false;
    this->P = false;
    this->cont = "";
    this->dest = "";
    this->ruta = "";
}

string Ejecutar::obtenerFecha(){
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    stringstream ss_year;
    ss_year << timePtr->tm_year+1900;
    string Year = ss_year.str();

    stringstream ss_month;
    ss_month << timePtr->tm_mon+1;
    string Month = ss_month.str();
    if(atoi(Month.c_str()) < 10)
        Month = "0"+Month;

    stringstream ss_day;
    ss_day << timePtr->tm_mday;
    string Day = ss_day.str();
    if(atoi(Day.c_str()) < 10)
        Day = "0"+Day;

    stringstream ss_hour;
    ss_hour << timePtr->tm_hour;
    string Hour = ss_hour.str();
    if(atoi(Hour.c_str()) < 10)
        Hour = "0"+Hour;

    stringstream ss_min;
    ss_min << timePtr->tm_min;
    string Min = ss_min.str();
    if(atoi(Min.c_str()) < 10)
        Min = "0"+Min;

    stringstream ss_sec;
    ss_sec << timePtr->tm_sec;
    string Sec = ss_sec.str();
    if(atoi(Sec.c_str()) < 10)
        Sec = "0"+Sec;

    return "F " + Day +"/"+ Month+"/"+Year+" H "+Hour+":"+Min+":"+Sec;
}

string Ejecutar::obtenerFirma(){
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    stringstream ss_year;
    ss_year << timePtr->tm_year+1900;
    string Year = ss_year.str();

    stringstream ss_month;
    ss_month << timePtr->tm_mon+1;
    string Month = ss_month.str();
    if(atoi(Month.c_str()) < 10)
        Month = "0"+Month;

    stringstream ss_day;
    ss_day << timePtr->tm_mday;
    string Day = ss_day.str();
    if(atoi(Day.c_str()) < 10)
        Day = "0"+Day;

    stringstream ss_hour;
    ss_hour << timePtr->tm_hour;
    string Hour = ss_hour.str();
    if(atoi(Hour.c_str()) < 10)
        Hour = "0"+Hour;

    stringstream ss_min;
    ss_min << timePtr->tm_min;
    string Min = ss_min.str();
    if(atoi(Min.c_str()) < 10)
        Min = "0"+Min;

    stringstream ss_sec;
    ss_sec << timePtr->tm_sec;
    string Sec = ss_sec.str();
    if(atoi(Sec.c_str()) < 10)
        Sec = "0"+Sec;

    string Fecha = Month+Day+Year+Hour+Min+Sec;
    return Fecha;
}

string Ejecutar::intToString(int num)
{
    std::string numAsStr;

    while (num)
    {
        char toInsert = (num % 10) + 48;
        numAsStr.insert(0, 1, toInsert);

        num /= 10;
    }
    return numAsStr;
}

QString Ejecutar::traducirPermisos(int permisos){
    if(permisos >= -1 && permisos <= 777){

    }
}
