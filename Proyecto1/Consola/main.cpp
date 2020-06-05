#include "Analizador/Nodo.h"
#include "iostream"
#include "Analizador/parser.h"
#include "Analizador/scanner.h"
#include "Analizador/Graficar.h"
#include "Ejecutar.h"
#include <QString>

extern int yyparse(); //
extern Nodo *raiz; // Raiz del arbol
extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;

using namespace::std;
int salir = 1;

int salida(){
    if(salir == 1){
        return 1;
    }else{
        return 0;
    }
}

int main()
{
    while (salir == 1) {
        string texto;
        cout << "Bienvenido, comience escribiendo un comando ... " << endl << "> ";
        getline(cin, texto);
        if(salida() == 1){
            QString entrada = QString::fromStdString(texto);
            yy_scan_string(entrada.toUtf8().constData());
            linea = 0;
            columna = 0;
            yylineno = 0;
            if(yyparse()==0){
                Graficar *graficar = new Graficar(raiz);
                graficar->generarImagen();
                Ejecutar *ejecutar = new Ejecutar();
                ejecutar->ejecutar(raiz);
            }
        }else return 0;
    }
    return 0;
}
