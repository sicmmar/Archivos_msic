#include "Graficar.h"
#include <QString>
#include <fstream>
#include <iostream>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include "Nodo.h"
Graficar::Graficar(Nodo *raiz)
{
    this->grafo = "";
    this->raiz = raiz;
    this->contador = 0;
}

QString Graficar::graficar()
{
    grafo = "digraph G{";
    grafo += "node[shape=\"box\"];";
    grafo += "NodoAST0[label=\"" + escapar(QString::number(raiz->tipo)+raiz->valor)  + "\"];\n";
    this->contador = 1;
    recorrerAST("NodoAST0", raiz);
    grafo += "}";
    return grafo;
}

void Graficar::recorrerAST(QString padre, Nodo *hijo)
{
    int x = 0;
    for (x = 0 ; x < hijo->hijos.count() ; x++)
    {
        Nodo NodoAST = hijo->hijos[x];
        QString nombreHijo = "NodoAST" +  QString::number(contador);//  this->contador;
        grafo += nombreHijo + "[label=\"" + escapar(QString::number(NodoAST.tipo) + NodoAST.valor)  + "\"];\n";
        grafo += padre + "->" + nombreHijo + ";\n";
        contador++;
        recorrerAST(nombreHijo, &NodoAST);
    }
}

QString Graficar::escapar(QString cadena)
{
    cadena = cadena.replace("\\", "\\\\");
    cadena = cadena.replace("\"", "\\\"");
    return cadena;
}

void Graficar:: generarImagen()
{
    QFileInfo fi("temp");

    graficar();
    QString grafoDOT = this->grafo;
    QFile qFile("grafo.txt");
    if(qFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&qFile); out << grafoDOT;
        qFile.close();
    }
    //"dot -Tjpg " + fileName + " -o " + fileName.Replace(".txt", ".jpg")
    QString cadenaComando = "dot -Tjpg grafo.txt -o grafo.jpg ";

    system(cadenaComando.toUtf8().constData());
/*    std::ofstream myfile;
    myfile.open ("grafo.txt",std::ios_base::app);
    myfile << grafoDOT.toStdString();
    myfile.close();
*/
}
