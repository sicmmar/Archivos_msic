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
%token<TEXT> rmkfs;
%token<TEXT> rlogin;
%token<TEXT> rusr;
%token<TEXT> rpwd;
%token<TEXT> rlogout;
%token<TEXT> rmkgrp;
%token<TEXT> rrmgrp;
%token<TEXT> rmkusr;
%token<TEXT> rgrp;
%token<TEXT> rrmusr;
%token<TEXT> rchmod;
%token<TEXT> rugo;
%token<TEXT> rmkfile;
%token<TEXT> rcont;
%token<TEXT> rcat;
%token<TEXT> rfile;
%token<TEXT> rrem;
%token<TEXT> redit;
%token<TEXT> rren;
%token<TEXT> rmkdir;
%token<TEXT> rcp;
%token<TEXT> rdest;
%token<TEXT> rmv;
%token<TEXT> rchown;
%token<TEXT> rchgrp;
%token<TEXT> rpause;
%token<TEXT> rruta;
%token<TEXT> rfind;
%token<TEXT> rr;
%token<TEXT> rp;
%token<TEXT> numero;
%token<TEXT> iden;
%token<TEXT> cadena;
%token<TEXT> permisos;
%token<TEXT> nombre;
%token<TEXT> rutaRaiz;

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
            $$ = new Nodo(@1.first_line, @1.first_column,-1);
            $$->agregar(*$1);
        }
;

COMANDO: rmkdisk LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,0);
            $$->agregar(*$2);
        }
        | rrmdisk LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,5);
            $$->agregar(*$2);
        }
        | rfdisk LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,6);
            $$->agregar(*$2);
        }
        | rmount LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,11);
            $$->agregar(*$2);
        }
        | runmount LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,12);
            $$->agregar(*$2);
        }
        | rrep LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,14);
            $$->agregar(*$2);
        }
        | rexec LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,15);
            $$->agregar(*$2);
        }
        | rmkfs LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,31);
            $$->agregar(*$2);
        }
        | rlogin LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,32);
            $$->agregar(*$2);
        }
        | rlogout
        {
            $$ = new Nodo(@1.first_line, @1.first_column,33);
        }
        | rmkgrp LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,34);
            $$->agregar(*$2);
        }
        | rrmgrp LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,35);
            $$->agregar(*$2);
        }
        | rmkusr LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,36);
            $$->agregar(*$2);
        }
        | rrmusr LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,37);
            $$->agregar(*$2);
        }
        | rchmod LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,38);
            $$->agregar(*$2);
        }
        | rmkfile LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,39);
            $$->agregar(*$2);
        }
        | rcat LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,40);
            $$->agregar(*$2);
        }
        | rrem LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,41);
            $$->agregar(*$2);
        }
        | redit LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,42);
            $$->agregar(*$2);
        }
        | rren LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,43);
            $$->agregar(*$2);
        }
        | rmkdir LPARAM
        {
           $$ = new Nodo(@1.first_line, @1.first_column,44);
           $$->agregar(*$2);
        }
        | rcp  LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,45);
            $$->agregar(*$2);
        }
        | rmv LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,46);
            $$->agregar(*$2);
        }
        | rchown LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,47);
            $$->agregar(*$2);
        }
        | rchgrp LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,48);
            $$->agregar(*$2);
        }
        | rpause
        {
            $$ = new Nodo(@1.first_line, @1.first_column,49);
        }
        | rr
        {
            $$ = new Nodo(@1.first_line, @1.first_column,63);
        }
        | rp
        {
            $$ = new Nodo(@1.first_line, @1.first_column,64);
        }
        | rfind LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,51);
            $$->agregar(*$2);
        }
        | error LPARAM
        {
            $$ = new Nodo(@1.first_line, @1.first_column,-3);
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
            $$ = new Nodo(@1.first_line, @1.first_column,-2);
            $$->agregar(*$2);
        }
;

PARAMETRO : rsize igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,1);
            $$->agregar(*$3);
        }
        | rfit igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,2);
            $$->agregar(*$3);
        }
        | runit igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,3);
            $$->agregar(*$3);
        }
        | rpath igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,4);
            $$->agregar(*$3);
        }
        | rtype igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,7);
            $$->agregar(*$3);
        }
        | rdelete igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,9);
            $$->agregar(*$3);
        }
        | rname igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,10);
            $$->agregar(*$3);
        }
        | radd igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,8);
            $$->agregar(*$3);
        }
        | rid igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,13);
            $$->agregar(*$3);
        }
        | rusr igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,55);
            $$->agregar(*$3);
        }
        | rpwd igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,56);
            $$->agregar(*$3);
        }
        | rgrp igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,57);
            $$->agregar(*$3);
        }
        | rugo igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,58);
            $$->agregar(*$3);
        }
        | rcont igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,59);
            $$->agregar(*$3);
        }
        | rfile igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,60);
            $$->agregar(*$3);
        }
        | rdest igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,61);
            $$->agregar(*$3);
        }
        | rruta igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,62);
            $$->agregar(*$3);
        }
        | error igual DATO
        {
            $$ = new Nodo(@1.first_line, @1.first_column,-3);
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
    | permisos
    {
        $$ = new Nodo(@1.first_line, @1.first_column,53,$1);
    }
    | nombre
    {
        $$ = new Nodo(@1.first_line, @1.first_column,24,$1);
    }
    | rutaRaiz
    {
        $$ = new Nodo(@1.first_line, @1.first_column,65,$1);
    }
    | rfile
    {
        $$ = new Nodo(@1.first_line, @1.first_column,24,$1);
    }
    | error
    {
        $$ = new Nodo(@1.first_line, @1.first_column,-3);
    }
;

%%
