%{
#include "scanner.h"//se importa el header del analisis sintactico
#include "Nodo.h"
#include "qdebug.h"
#include <iostream>
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
extern Nodo *raiz; // Raiz del arbol

int yyerror(const char* mens)
{

    std::cout << mens <<" "<<yytext<< std::endl;
    return 0;
}
%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output "parser.cpp"
%define parse.error verbose
%locations

%union{
//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
class Nodo *nodito;
}

//TERMINALES DE TIPO TEXT, SON STRINGS
%token<TEXT> ruta;
%token<TEXT> guion;
%token<TEXT> igual;
%token<TEXT> rmkdisk;
%token<TEXT> rsize;
%token<TEXT> rfit;
%token<TEXT> runit;
%token<TEXT> rpath;
%token<TEXT> rrmdisk;
%token<TEXT> rfdisk;
%token<TEXT> rtype;
%token<TEXT> radd;
%token<TEXT> rdelete;
%token<TEXT> rname;
%token<TEXT> rmount;
%token<TEXT> runmount;
%token<TEXT> rid;
%token<TEXT> rrep;
%token<TEXT> rexec;
%token<TEXT> numero;
%token<TEXT> iden;
%token<TEXT> cadena;

/*No terimanes*/
%type<nodito> INICIO;
%type<nodito> LCOMANDOS;
%type<nodito> COMANDO;
%type<nodito> LPARAM;
%type<nodito> PARAMETRO;
%type<nodito> DATO;

%start INICIO
%%

INICIO : LCOMANDOS { raiz = $$; }
;

LCOMANDOS: LCOMANDOS COMANDO
        {
            $$=$1;
            $$->agregar(*$2);
        }
        | COMANDO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,-1,"COMANDO");
            $$->agregar(*$1);
        }
;

COMANDO: rmkdisk LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,0,"MKDISK");
            $$->agregar(*$2);
        }
        | rrmdisk LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,5,"RMDISK");
            $$->agregar(*$2);
        }
        | rfdisk LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,6,"FDISK");
            $$->agregar(*$2);
        }
        | rmount LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,11,"MOUNT");
            $$->agregar(*$2);
        }
        | runmount LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,12,"UNMOUNT");
            $$->agregar(*$2);
        }
        | rrep LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,14,"REP");
            $$->agregar(*$2);
        }
        | rexec LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,15,"EXEC");
            $$->agregar(*$2);
        }
        | error LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,-3,"ERROR");
            $$->agregar(*$2);
        }
;

LPARAM : LPARAM guion PARAMETRO
        {
            $$=$1;
            $$->agregar(*$3);
        }
        | guion PARAMETRO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,-2,"PARAMETRO");
            $$->agregar(*$2);
        }
;

PARAMETRO : rsize igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,1,"SIZE");
            $$->agregar(*$3);
        }
        | rfit igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,2,"FIT");
            $$->agregar(*$3);
        }
        | runit igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,3,"UNIT");
            $$->agregar(*$3);
        }
        | rpath igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,4,"PATH");
            $$->agregar(*$3);
        }
        | rtype igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,7,"TYPE");
            $$->agregar(*$3);
        }
        | rdelete igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,9,"DELETE");
            $$->agregar(*$3);
        }
        | rname igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,10,"NAME");
            $$->agregar(*$3);
        }
        | radd igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,8,"ADD");
            $$->agregar(*$3);
        }
        | rid igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,13,"ID");
            $$->agregar(*$3);
        }
        | error igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,-3,"ERROR");
            $$->agregar(*$3);
        }
;

DATO: numero
    {
        $$ = new Nodo(@1.first_line, @1.first_column,23,$1);
    }
    | iden
    {
        $$ = new Nodo(@1.first_line, @1.first_column,24,$1);
    }
    | ruta
    {
        $$ = new Nodo(@1.first_line, @1.first_column,25,$1);
    }
    | cadena
    {
        $$ = new Nodo(@1.first_line, @1.first_column,26,$1);
    }
    | error
    {
        $$ = new Nodo(@1.first_line, @1.first_column,-3,"ERROR");
    }
;

%%
