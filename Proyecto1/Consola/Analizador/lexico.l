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
comentario "#"[^\n]*"\n"

%x COM

%%
INITIAL
{
{comentario}             {}
{ruta}            {   strcpy(yylval.TEXT, yytext); return ruta;}
{numero}          {   strcpy(yylval.TEXT, yytext); return numero;}
"-"          {   strcpy(yylval.TEXT, yytext); return guion; }
"="          {   strcpy(yylval.TEXT, yytext); return igual; }
"mkdisk"          {   strcpy(yylval.TEXT, yytext); return rmkdisk; }
"size"          {   strcpy(yylval.TEXT, yytext); return rsize; }
"fit"           {   strcpy(yylval.TEXT, yytext); return rfit; }
"unit"          {   strcpy(yylval.TEXT, yytext); return runit; }
"path"          {   strcpy(yylval.TEXT, yytext); return rpath; }
"rmdisk"        {   strcpy(yylval.TEXT, yytext); return rrmdisk; }
"fdisk"         {   strcpy(yylval.TEXT, yytext); return rfdisk; }
"type"          {   strcpy(yylval.TEXT, yytext); return rtype; }
"add"           {   strcpy(yylval.TEXT, yytext); return radd; }
"delete"        {   strcpy(yylval.TEXT, yytext); return rdelete; }
"name"          {   strcpy(yylval.TEXT, yytext); return rname; }
"mount"         {   strcpy(yylval.TEXT, yytext); return rmount; }
"unmount"       {   strcpy(yylval.TEXT, yytext); return runmount; }
"id"            {   strcpy(yylval.TEXT, yytext); return rid; }
"rep"           {   strcpy(yylval.TEXT, yytext); return rrep; }
"exec"          {   strcpy(yylval.TEXT, yytext); return rexec; }
{iden}            {   strcpy(yylval.TEXT, yytext); return iden;}
{cadena}          {   strcpy(yylval.TEXT, yytext); return cadena;}
[ \t\n\r]     { }
.               {
                    strcpy(yylval.TEXT, yytext);
                    std::cout << " Error Lexico "<< yytext << std::endl;
                }
}
<COM>"\n" { BEGIN INITIAL; };
<COM>.;
%%
