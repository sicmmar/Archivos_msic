#include "Analizador/Nodo.h"
#include "iostream"
#include "Analizador/parser.h"
#include "Analizador/scanner.h"
#include "Analizador/Graficar.h"
#include "Montar/Montar.h"
#include "Ejecutar.h"
#include "Usuario.h"
#include <QString>

extern int yyparse(); //
extern Nodo *raiz; // Raiz del arbol
extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;

using namespace::std;
int salir = 1;
Montar *listaParticiones = new Montar();
Usuario *usuario = new Usuario();

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
        cout << "Bienvenido, comience escribiendo un comando ... " << endl << " ";
        getline(cin, texto);
        if(salida() == 1){
            QString entrada = QString::fromStdString(texto);
            if(entrada.contains("exec")){
                string path = entrada.replace("exec -path=", "").toStdString();
                string linea;
                entrada = "";
                ifstream archivo(path);
                if(archivo.is_open()){
                    while (getline(archivo, linea)) {
                        entrada += QString::fromStdString(linea) + "\n";
                    }
                    archivo.close();
                }else cout << "error: el archivo " << path << " no existe" << endl;
            }

            yy_scan_string(entrada.toUtf8().constData());
            linea = 0;
            columna = 0;
            yylineno = 0;
            if(yyparse()==0){
                Graficar *graficar = new Graficar(raiz);
                graficar->generarImagen();
                Ejecutar *ejecutar = new Ejecutar();
                ejecutar->ejecutar(raiz, listaParticiones, usuario);
                listaParticiones = ejecutar->listaParticiones;
                usuario = ejecutar->usuario;
            }
        }else return 0;
    }

    return 0;
}
