#include "Ejecutar.h"
#include "iostream"
#include "time.h"
#include "ctime"
#include <stdlib.h>
#include <sstream>

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
    QString mbr_fecha_creacion;
    int mbr_signature;
    char disk_fit;
    Partition mbr_partition[4];
};

Ejecutar::Ejecutar(){
    this->raiz = NULL;
}


void Ejecutar::ejecutar(Nodo *raiz){
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
        mbr.mbr_fecha_creacion = this->obtenerFecha();
        mbr.mbr_signature = this->obtenerFirma();
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
                    cout << " ::Creando directorio " << endl;
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

    if(parametrosObligatorios(2)){
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

bool Ejecutar::parametrosObligatorios(int comando){
    if(this->parametrosCorrectos(comando))return true;
    else{
        cout << "error: Verifique parametros, hacen falta algunos" << endl;
        return false;
    }
}

bool Ejecutar::parametrosCorrectos(int comando){ //parametros obligatorios
    switch (comando) {
    case 1: //mkdisk
        {if(this->size != "" && this->path != "")return true;}
    case 2: //rmdisk
        {if(this->path != "")return true;}
    case 3: //fdisk
        {if(this->size != "" && this->path != "" && this->nombre != "")return true;}
    case 4: //mount
        {if(this->path != "" && this->nombre != "") return true;}
    case 5: //unmount
        {if(this->id != "") return true;}
    case 6: //rep
        {if(this->nombre != "" && this->path != "" && this->id != "") return true;}
    case 7: //exec
        {if(this->path != "") return true;}
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

QString Ejecutar::obtenerFecha(){
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

    QString Fecha = "F " + QString::fromStdString(Day) +"/"+
            QString::fromStdString(Month)+"/"+QString::fromStdString(Year)+
            " H "+QString::fromStdString(Hour)+":"+QString::fromStdString(Min)+":"+QString::fromStdString(Sec);

    return Fecha;
}

int Ejecutar::obtenerFirma(){
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

    QString Fecha = QString::fromStdString(Year)+QString::fromStdString(Month)+QString::fromStdString(Day)+
            QString::fromStdString(Hour)+QString::fromStdString(Min)+QString::fromStdString(Sec);
    int sign = Fecha.toInt();
    return sign;
}
