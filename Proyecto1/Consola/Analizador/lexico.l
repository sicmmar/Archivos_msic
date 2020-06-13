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

permisos [0-7][0-7][0-7]
numero "-"?[0-9]+("."[0-9]+)?
iden [A-Za-z0-9_]+
nombre {iden}"."{iden}
ruta ("/"{iden})+"."{iden}
cadena "\""[^"\""]*"\""
comentario "#"[^\n]*"\n"
rr "-"[rR][ \n\t\r]
rp "-"[pP][ \n\t\r]


%%
INITIAL
{
{comentario}             {}
"/"                 {   strcpy(yylval.TEXT, yytext); return rutaRaiz;}
{ruta}              {   strcpy(yylval.TEXT, yytext); return ruta;}
{permisos}          {   strcpy(yylval.TEXT, yytext); return permisos;}
{numero}            {   strcpy(yylval.TEXT, yytext); return numero;}
{rr}            {   strcpy(yylval.TEXT, yytext); return rr;}
{rp}            {   strcpy(yylval.TEXT, yytext); return rp;}
"-"          {   strcpy(yylval.TEXT, yytext); return guion; }
"="          {   strcpy(yylval.TEXT, yytext); return igual; }
"mkdisk"        {   strcpy(yylval.TEXT, yytext); return rmkdisk; }
"mkfs"          {   strcpy(yylval.TEXT, yytext); return rmkfs; }
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
"login"         {   strcpy(yylval.TEXT, yytext); return rlogin; }
"usr"           {   strcpy(yylval.TEXT, yytext); return rusr; }
"pwd"           {   strcpy(yylval.TEXT, yytext); return rpwd; }
"logout"        {   strcpy(yylval.TEXT, yytext); return rlogout; }
"mkgrp"         {   strcpy(yylval.TEXT, yytext); return rmkgrp; }
"rmgrp"         {   strcpy(yylval.TEXT, yytext); return rrmgrp; }   
"mkusr"         {   strcpy(yylval.TEXT, yytext); return rmkusr; }
"grp"           {   strcpy(yylval.TEXT, yytext); return rgrp; }
"rmusr"         {   strcpy(yylval.TEXT, yytext); return rrmusr; }
"chmod"         {   strcpy(yylval.TEXT, yytext); return rchmod; }
"ugo"           {   strcpy(yylval.TEXT, yytext); return rugo; }
"mkfile"        {   strcpy(yylval.TEXT, yytext); return rmkfile; }
"cont"          {   strcpy(yylval.TEXT, yytext); return rcont; }
"cat"           {   strcpy(yylval.TEXT, yytext); return rcat; }
"file"          {   strcpy(yylval.TEXT, yytext); return rfile; }
"rem"           {   strcpy(yylval.TEXT, yytext); return rrem; }
"edit"          {   strcpy(yylval.TEXT, yytext); return redit; }
"ren"           {   strcpy(yylval.TEXT, yytext); return rren; }
"mkdir"         {   strcpy(yylval.TEXT, yytext); return rmkdir; }
"cp"            {   strcpy(yylval.TEXT, yytext); return rcp; }
"dest"          {   strcpy(yylval.TEXT, yytext); return rdest; }
"mv"            {   strcpy(yylval.TEXT, yytext); return rmv; }
"chown"         {   strcpy(yylval.TEXT, yytext); return rchown; }
"chgrp"         {   strcpy(yylval.TEXT, yytext); return rchgrp; }
"pause"         {   strcpy(yylval.TEXT, yytext); return rpause; }
"ruta"          {   strcpy(yylval.TEXT, yytext); return rruta; }
"find"          {   strcpy(yylval.TEXT, yytext); return rfind; }
{nombre}            {   strcpy(yylval.TEXT, yytext); return nombre;}
{iden}              {   strcpy(yylval.TEXT, yytext); return iden;}
{cadena}            {   strcpy(yylval.TEXT, yytext); return cadena;}
[ \t\n\r]     { }
.               {
                    strcpy(yylval.TEXT, yytext);
                    std::cout << " Error Lexico "<< yytext << std::endl;
                }
}
%%
