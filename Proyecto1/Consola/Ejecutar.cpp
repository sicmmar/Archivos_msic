#include "Ejecutar.h"
#include <iostream>
#include <fstream>
#include "time.h"
#include "ctime"
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
struct Partition{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
};

struct MBR{
    int mbr_tamano;
    char mbr_fecha_creacion[32];
    int mbr_signature;
    char disk_fit;
    Partition mbr_partition[4];
};

Ejecutar::Ejecutar(){
    this->raiz = NULL;
}


void Ejecutar::ejecutar(Nodo *raiz, Montar *lista){
    this->listaParticiones = lista;
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
        mbr.disk_fit = this->fit.toStdString()[0];

        int tamano = 0;
        if(this->unit.toUpper() == "M") tamano = this->size.toInt() * (1024 * 1024);
        else if(this->unit.toUpper() == "K") tamano = this->size.toInt() * 1024;
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

            QString path2 = this->path.replace(".disk", "_RAID.disk");
            this->path.replace("_RAID.disk", ".disk");
            char dir1[this->path.length()], dir2[path2.length()];
            strcpy(dir1,this->path.toStdString().c_str());
            strcpy(dir2,path2.toStdString().c_str());
            FILE* disco1 = fopen(dir1, "wb");
            FILE* disco2 = fopen(dir2, "wb");
            if(disco1 != NULL && disco2 != NULL){
                int fin=(tamano/1024);
                char buffer[1024];
                int i=0;
                for(i=0;i<1024;i++){
                    buffer[i]='\0';
                }
                int j=0;
                while(j!=fin){
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
            if(f1 != NULL && f2 != NULL){
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
       strcpy(comando,path2.replace(".disk", "_RAID.disk").toStdString().c_str());
       FILE* d2 = fopen(comando, "r+b");
       MBR mbr;
       if(d1 != NULL && d2 != NULL){
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
           if(this->size != "" && accionEjecutada == 0){ //crear particion
                int tamano = this->size.toInt();
                if(this->unit == "K")tamano*=1024;
                else if(this->unit == "M")tamano*=(1024*1024);

                if(tamano < tamanoDisco){
                    if((primarias + extendidas) == 0){ // la primer particion
                        if(this->type == "P" || this->type == "p" || this->type == "E" || this->type == "e"){ // primaria
                            mbr.mbr_partition[0].part_status = 'A';
                            mbr.mbr_partition[0].part_type = this->type.toStdString().c_str()[0];
                            mbr.mbr_partition[0].part_fit = this->fit.toStdString().c_str()[0];
                            mbr.mbr_partition[0].part_start = sizeof (MBR);
                            mbr.mbr_partition[0].part_size = tamano;
                            strcpy(mbr.mbr_partition[0].part_name,this->nombre.toStdString().c_str());
                            nueva = mbr.mbr_partition[0];
                            fseek(d1,nueva.part_start,SEEK_SET);
                            fseek(d2,nueva.part_start,SEEK_SET);

                            int fin=(tamano/1024);
                            char buffer[1024];
                            for(int i=0;i<1024;i++){
                                buffer[i]='1';
                            }
                            int j=0;
                            while(j!=fin){
                                fwrite(&buffer,1024 , 1, d1);
                                fwrite(&buffer, 1024, 1, d2);
                                j++;
                            }
                        }else if(this->type == "L" || this->type == "l") cout << "error: no se pueden agregar particiones logicas sin una particion extendida" << endl;
                        accionEjecutada = 1;
                    }else if((primarias + extendidas) > 0 && (primarias + extendidas) < 4){ // ya hay una particion
                        if(this->fit == "BF"){ // el mejor ajuste
                            //if(mbr.mbr_partition[1])
                        }
                    }else cout << "error: no se pueden agregar mas particiones " << endl;
                }else cout << "error: no se puede agregar espacio mas grande que el disco " << endl;

           }if(this->add != "" && accionEjecutada == 0){ //modificar particion

           }if(this->del != "" && accionEjecutada == 0){ // eliminar particion

           }if(accionEjecutada == 0) cout << "error: se necesita el parametro 'size', 'add' o 'delete' para accionar" << endl;
       }

       fseek(d1,0,SEEK_SET);
       fwrite(&mbr, sizeof(MBR), 1, d1);//escribe mbr2
       fclose(d1);
       fseek(d2,0,SEEK_SET);
       fwrite(&mbr, sizeof(MBR), 1, d2);//escribe mbr2
       fclose(d2);
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
            if(this->path.split(".")[1].toUpper() == "JPG" || this->path.split(".")[1].toUpper() == "JPEG" || this->path.split(".")[1].toUpper() == "PNG"){
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
                QString texto = "digraph partition{\n";
                QString pathDisco = this->listaParticiones->listaParticion.at(posicionParticion).path;
                strcpy(comando, pathDisco.toStdString().c_str());
                FILE* f1= fopen(comando, "r+b");
                fseek(f1,0,SEEK_SET);// estableciendo puntero al inicio
                if(f1 != NULL){
                    fread(&mbr, sizeof (MBR), 1, f1);
                    int tamanoDisco = mbr.mbr_tamano;
                    if(this->nombre.toUpper() == "MBR"){

                    }else if(this->nombre.toUpper() == "DISK"){
                        int numNodo = 0;
                        texto +="graph [nodesep=0.01, rankdir=\"LR\", label=\"" + pathDisco + "\"];\n";
                        texto += "edge [color=white, arrowsize=.01, weight=.01, penwidth=.01];\n";
                        texto += "node [shape=record, height=1.25];\n"
                        cout << "size of MBR " << sizeof (MBR) << endl;
                        texto += QString::number(numNodo) + " [label=\"MBR\\n0.00028%\", width=.01];\n";
                        cout << texto.toStdString() << endl;

                    }
                }

                fclose(f1);

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
        if(d1 != NULL){
            fseek(d1,0,SEEK_SET);
            fread(&mbr, sizeof (MBR), 1, d1);
            bool encontrado = false;
            int i = 0;
            char nombre[16];
            strcpy(nombre, this->nombre.toStdString().c_str());
            while(i < 4 && !encontrado){
                if(strcmp(nombre, mbr.mbr_partition[i].part_name) == 0){
                    Particion part = Particion(this->path, this->nombre);
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

    if(parametrosObligatorios(5))this->listaParticiones->quitarParticion(this->id);
}

bool Ejecutar::parametrosObligatorios(int comando){
    if(this->parametrosCorrectos(comando))return true;
    else{
        cout << "error: verifique parametros, hace(n) falta uno(s)" << endl;
        return false;
    }
}

bool Ejecutar::parametrosCorrectos(int comando){ //parametros obligatorios
    if(comando == 1 && this->size != "" && this->path != "")return true;
    else if(comando == 8 && this->path != "")return true;
    else if(comando == 4 && this->path != "" && this->nombre != "") return true;
    else if(comando == 5 && this->id != "") return true;
    else if(comando == 6 && this->nombre != "" && this->path != "" && this->id != ""){
        if(this->nombre.toUpper() == "MBR" || this->nombre.toUpper() == "DISK")return true;
        else{
            cout << "error: el reporte de " << this->nombre.toStdString() << " no existe" << endl;
            return false;
        }
    }
    else return false;
}

void Ejecutar::colocarParametros(Nodo *raiz){
    QString v = raiz->hijos.at(0).valor;
    QString &valor = v.replace("\"", "").replace(" ", "");
    switch (raiz->tipo) {
        case 1: // size
            {
                if(raiz->hijos.at(0).tipo == 23){
                    long tamano = valor.toLong();
                    if(tamano > 0) this->size = valor;
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
                if(valor.contains('/') && valor.contains('.')) this->path = valor;
                else cout << "error: Verificar el directorio " << valor.toStdString() << endl;
            }
            break;
        case 7: // type
            {
                if(valor.toUpper() == "P" || valor.toUpper() == "E" || valor.toUpper() == "L") this->type = valor;
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
                else cout << "error: Se espera un identificador para 'id'" << endl;
            }
            break;
        default:
            cout << "error: Parametro desconocido " << endl;
    }
}

void Ejecutar::limpiarVariables(){
    this->size = "";
    this->nombre = "";
    this->unit = "";
    this->type = "";
    this->path = "";
    this->fit = "";
    this->del = "";
    this->add = "";
    this->id = "";
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
