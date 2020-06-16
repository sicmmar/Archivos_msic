#include "Montar.h"
#include "Particion.h"
#include <QString>
#include <QList>
#include <iostream>

using namespace std;

Montar::Montar(){
    this->listaDiscos = QList<Disco>();
    this->listaParticion = QList<Particion>();
    this->fechaUnmount = "";
}

void Montar::agregarParticion(Particion nueva){
    int posParticion = buscarParticion(nueva.name, nueva.path, "\0");
    if(posParticion < 0){
        int posicion = buscarDiscos(nueva.path);
        if(posicion < 0){
            nueva.disco = (char)(this->listaDiscos.length() + 97);
            this->listaDiscos.append(Disco(nueva.path));
            posicion = buscarDiscos(nueva.path);
        }else{
            nueva.disco = (char)(posicion + 97);
            Disco d = this->listaDiscos.at(posicion);
            d.numParticiones += 1;
            this->listaDiscos.replace(posicion, d);
        }
        nueva.iden = "vd";
        nueva.iden.append(nueva.disco);
        nueva.iden.append(QString::number(this->listaDiscos.at(posicion).numParticiones));
        this->listaParticion.append(nueva);
        cout << " ::Particion montada con el id " << nueva.iden.toStdString() << endl;
        // mount -path=/home/g.disk -name=particion2
    }else cout << "error: la particion " << nueva.name.toStdString() << " del disco " << nueva.path.toStdString() << " ya esta montada" << endl;

}

void Montar::quitarParticion(QString id, string fecha){
    int posParticion = buscarParticion("\0", "\0", id);
    if(posParticion >= 0){
        string respuesta;
        cout << " ::Seguro que desea desmontar la particion " << id.toStdString() << "? [Y/n] ";
        getline(cin, respuesta);
        if(strcmp(respuesta.c_str(), "n") == 0 || strcmp(respuesta.c_str(), "N") == 0) cout << " ::La particion " << id.toStdString() << " no se ha desmontado" << endl;
        else{
            this->fechaUnmount = fecha;
            this->listaParticion.removeAt(posParticion);
            cout << " ::Particion " << id.toStdString() << " desmontada " << endl;
        }
    }
    else cout << "error: la particion " << id.toStdString() << " no esta montada" << endl;
}

int Montar::buscarParticion(QString nombre, QString path, QString iden){
    for(int i = 0; i < this->listaParticion.length(); i++){
        if(this->listaParticion.at(i).iden == iden) return i;
        else if(this->listaParticion.at(i).name == nombre && this->listaParticion.at(i).path == path) return i;
    }
    return -1;
}

Particion Montar::devolverParticion(QString iden){
    int posParticion = buscarParticion("\0", "\0", iden);
    if(posParticion >= 0)
        return this->listaParticion.at(posParticion);
    else return Particion();
}

int Montar::buscarDiscos(QString path){
    for(int i = 0; i < this->listaDiscos.length(); i++){
        if(this->listaDiscos.at(i).path == path) return i;
    }

    return -1;
}
