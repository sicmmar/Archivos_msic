/* A Bison parser, made by GNU Bison 3.6.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ruta = 258,                    /* ruta  */
    guion = 259,                   /* guion  */
    igual = 260,                   /* igual  */
    rmkdisk = 261,                 /* rmkdisk  */
    rsize = 262,                   /* rsize  */
    rfit = 263,                    /* rfit  */
    runit = 264,                   /* runit  */
    rpath = 265,                   /* rpath  */
    rrmdisk = 266,                 /* rrmdisk  */
    rfdisk = 267,                  /* rfdisk  */
    rtype = 268,                   /* rtype  */
    radd = 269,                    /* radd  */
    rdelete = 270,                 /* rdelete  */
    rname = 271,                   /* rname  */
    rmount = 272,                  /* rmount  */
    runmount = 273,                /* runmount  */
    rid = 274,                     /* rid  */
    rrep = 275,                    /* rrep  */
    rexec = 276,                   /* rexec  */
    rbf = 277,                     /* rbf  */
    rff = 278,                     /* rff  */
    rwf = 279,                     /* rwf  */
    rfull = 280,                   /* rfull  */
    rfast = 281,                   /* rfast  */
    rmbr = 282,                    /* rmbr  */
    rdisk = 283,                   /* rdisk  */
    numero = 284,                  /* numero  */
    iden = 285,                    /* iden  */
    cadena = 286                   /* cadena  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "sintactico.yy"

//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
class Nodo *nodito;

#line 101 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
