%option case-insensitive
%option yylineno
%{
#include <cstdlib>
#include "parser.h"
#include <QString>
#include <stdio.h>
#include <iostream>
#include "Nodo.h"
#include "qlist.h"

int yylex();
void yyerror(const char *s);
int linea=0; // Para contar lineas
int columna = 1; // para las columnas
int anterior = 0;
Nodo *raiz;
%}

%option header-file="scanner.h"
%option outfile="scanner.cpp"
%option noyywrap
%option nounput

numero "-"?[0-9]+("."[0-9]+)?
iden [A-Za-z_][A-Za-z0-9_]*
ruta ("/"{iden})+"."{iden}
cadena "\""[^"\""]*"\""

%x COM

%%
INITIAL
{
"#" {  BEGIN COM; }
{ruta}            {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ruta;}
{numero}          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return numero;}
"-"          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return guion; }
"="          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return igual; }
"mkdisk"          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rmkdisk; }
"size"          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rsize; }
"fit"           {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rfit; }
"unit"          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return runit; }
"path"          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rpath; }
"rmdisk"        {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rrmdisk; }
"fdisk"         {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rfdisk; }
"type"          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rtype; }
"add"           {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return radd; }
"delete"        {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rdelete; }
"name"          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rname; }
"mount"         {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rmount; }
"unmount"       {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return runmount; }
"id"            {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rid; }
"rep"           {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rrep; }
"exec"          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return rexec; }
{iden}            {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return iden;}
{cadena}          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cadena;}
"\t"            {
                    strcpy(yylval.TEXT, yytext); columna=26;
                }
[[:blank:]]     { columna++; }
"\n"            {linea++; columna = 0; anterior = 0;}
.               {
                    columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);
/*                    errorT *nuevoE = new errorT("Lexico",yytext,linea, columna);
                    listaErrores->append(*nuevoE);
*/
                    std::cout <<yytext <<" Error Lexico en la linea "<< linea << " Columna:"<< columna<<  std::endl;
                }
}
<COM>"\n" { linea++; columna = 0; BEGIN INITIAL; };
<COM>.;
%%
