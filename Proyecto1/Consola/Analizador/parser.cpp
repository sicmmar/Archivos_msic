/* A Bison parser, made by GNU Bison 3.6.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.6.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintactico.yy"

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

#line 89 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    rmkfs = 277,                   /* rmkfs  */
    rlogin = 278,                  /* rlogin  */
    rusr = 279,                    /* rusr  */
    rpwd = 280,                    /* rpwd  */
    rlogout = 281,                 /* rlogout  */
    rmkgrp = 282,                  /* rmkgrp  */
    rrmgrp = 283,                  /* rrmgrp  */
    rmkusr = 284,                  /* rmkusr  */
    rgrp = 285,                    /* rgrp  */
    rrmusr = 286,                  /* rrmusr  */
    rchmod = 287,                  /* rchmod  */
    rugo = 288,                    /* rugo  */
    rmkfile = 289,                 /* rmkfile  */
    rcont = 290,                   /* rcont  */
    rcat = 291,                    /* rcat  */
    rfile = 292,                   /* rfile  */
    rrem = 293,                    /* rrem  */
    redit = 294,                   /* redit  */
    rren = 295,                    /* rren  */
    rmkdir = 296,                  /* rmkdir  */
    rcp = 297,                     /* rcp  */
    rdest = 298,                   /* rdest  */
    rmv = 299,                     /* rmv  */
    rchown = 300,                  /* rchown  */
    rchgrp = 301,                  /* rchgrp  */
    rpause = 302,                  /* rpause  */
    rruta = 303,                   /* rruta  */
    rfind = 304,                   /* rfind  */
    rr = 305,                      /* rr  */
    rp = 306,                      /* rp  */
    numero = 307,                  /* numero  */
    iden = 308,                    /* iden  */
    cadena = 309,                  /* cadena  */
    permisos = 310,                /* permisos  */
    nombre = 311,                  /* nombre  */
    rutaRaiz = 312                 /* rutaRaiz  */
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

#line 202 "parser.cpp"

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
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ruta = 3,                       /* ruta  */
  YYSYMBOL_guion = 4,                      /* guion  */
  YYSYMBOL_igual = 5,                      /* igual  */
  YYSYMBOL_rmkdisk = 6,                    /* rmkdisk  */
  YYSYMBOL_rsize = 7,                      /* rsize  */
  YYSYMBOL_rfit = 8,                       /* rfit  */
  YYSYMBOL_runit = 9,                      /* runit  */
  YYSYMBOL_rpath = 10,                     /* rpath  */
  YYSYMBOL_rrmdisk = 11,                   /* rrmdisk  */
  YYSYMBOL_rfdisk = 12,                    /* rfdisk  */
  YYSYMBOL_rtype = 13,                     /* rtype  */
  YYSYMBOL_radd = 14,                      /* radd  */
  YYSYMBOL_rdelete = 15,                   /* rdelete  */
  YYSYMBOL_rname = 16,                     /* rname  */
  YYSYMBOL_rmount = 17,                    /* rmount  */
  YYSYMBOL_runmount = 18,                  /* runmount  */
  YYSYMBOL_rid = 19,                       /* rid  */
  YYSYMBOL_rrep = 20,                      /* rrep  */
  YYSYMBOL_rexec = 21,                     /* rexec  */
  YYSYMBOL_rmkfs = 22,                     /* rmkfs  */
  YYSYMBOL_rlogin = 23,                    /* rlogin  */
  YYSYMBOL_rusr = 24,                      /* rusr  */
  YYSYMBOL_rpwd = 25,                      /* rpwd  */
  YYSYMBOL_rlogout = 26,                   /* rlogout  */
  YYSYMBOL_rmkgrp = 27,                    /* rmkgrp  */
  YYSYMBOL_rrmgrp = 28,                    /* rrmgrp  */
  YYSYMBOL_rmkusr = 29,                    /* rmkusr  */
  YYSYMBOL_rgrp = 30,                      /* rgrp  */
  YYSYMBOL_rrmusr = 31,                    /* rrmusr  */
  YYSYMBOL_rchmod = 32,                    /* rchmod  */
  YYSYMBOL_rugo = 33,                      /* rugo  */
  YYSYMBOL_rmkfile = 34,                   /* rmkfile  */
  YYSYMBOL_rcont = 35,                     /* rcont  */
  YYSYMBOL_rcat = 36,                      /* rcat  */
  YYSYMBOL_rfile = 37,                     /* rfile  */
  YYSYMBOL_rrem = 38,                      /* rrem  */
  YYSYMBOL_redit = 39,                     /* redit  */
  YYSYMBOL_rren = 40,                      /* rren  */
  YYSYMBOL_rmkdir = 41,                    /* rmkdir  */
  YYSYMBOL_rcp = 42,                       /* rcp  */
  YYSYMBOL_rdest = 43,                     /* rdest  */
  YYSYMBOL_rmv = 44,                       /* rmv  */
  YYSYMBOL_rchown = 45,                    /* rchown  */
  YYSYMBOL_rchgrp = 46,                    /* rchgrp  */
  YYSYMBOL_rpause = 47,                    /* rpause  */
  YYSYMBOL_rruta = 48,                     /* rruta  */
  YYSYMBOL_rfind = 49,                     /* rfind  */
  YYSYMBOL_rr = 50,                        /* rr  */
  YYSYMBOL_rp = 51,                        /* rp  */
  YYSYMBOL_numero = 52,                    /* numero  */
  YYSYMBOL_iden = 53,                      /* iden  */
  YYSYMBOL_cadena = 54,                    /* cadena  */
  YYSYMBOL_permisos = 55,                  /* permisos  */
  YYSYMBOL_nombre = 56,                    /* nombre  */
  YYSYMBOL_rutaRaiz = 57,                  /* rutaRaiz  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_INICIO = 59,                    /* INICIO  */
  YYSYMBOL_LCOMANDOS = 60,                 /* LCOMANDOS  */
  YYSYMBOL_COMANDO = 61,                   /* COMANDO  */
  YYSYMBOL_LPARAM = 62,                    /* LPARAM  */
  YYSYMBOL_PARAMETRO = 63,                 /* PARAMETRO  */
  YYSYMBOL_DATO = 64                       /* DATO  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   194

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

#define YYMAXUTOK   312


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
  /* YYRLINEYYN -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    98,    98,   101,   106,   113,   118,   123,   128,   133,
     138,   143,   148,   153,   158,   162,   167,   172,   177,   182,
     187,   192,   197,   202,   207,   212,   217,   222,   227,   232,
     237,   241,   245,   249,   254,   261,   266,   273,   278,   283,
     288,   293,   298,   303,   308,   313,   318,   323,   328,   333,
     338,   343,   348,   353,   358,   365,   369,   373,   377,   381,
     385,   389,   393,   397
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ruta", "guion",
  "igual", "rmkdisk", "rsize", "rfit", "runit", "rpath", "rrmdisk",
  "rfdisk", "rtype", "radd", "rdelete", "rname", "rmount", "runmount",
  "rid", "rrep", "rexec", "rmkfs", "rlogin", "rusr", "rpwd", "rlogout",
  "rmkgrp", "rrmgrp", "rmkusr", "rgrp", "rrmusr", "rchmod", "rugo",
  "rmkfile", "rcont", "rcat", "rfile", "rrem", "redit", "rren", "rmkdir",
  "rcp", "rdest", "rmv", "rchown", "rchgrp", "rpause", "rruta", "rfind",
  "rr", "rp", "numero", "iden", "cadena", "permisos", "nombre", "rutaRaiz",
  "$accept", "INICIO", "LCOMANDOS", "COMANDO", "LPARAM", "PARAMETRO",
  "DATO", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312
};
#endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACTSTATE-NUM -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      99,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,   -42,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,   -42,     1,   -42,
     -42,     3,    57,   -42,     0,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   -42,   -42,     6,     7,    12,    13,    15,    16,    17,
      18,    21,    22,    23,    24,    26,    27,    29,    33,    34,
      35,   -42,     0,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42
};

  /* YYDEFACTSTATE-NUM -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,    31,
      32,     0,     0,     4,     0,    34,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      33,     1,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    63,    57,    62,    55,    56,    58,    59,    60,
      61,    54,    37,    38,    39,    40,    41,    44,    42,    43,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

  /* YYPGOTONTERM-NUM.  */
static const yytype_int16 yypgoto[] =
{
     -42,   -42,   -42,   -28,   149,   -41,    94
};

  /* YYDEFGOTONTERM-NUM.  */
static const yytype_int8 yydefgoto[] =
{
      -1,    31,    32,    33,    35,    81,   111
};

  /* YYTABLEYYPACT[STATE-NUM] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     102,    63,   103,    61,    62,    34,    82,    64,    65,    66,
      67,    83,    84,    68,    69,    70,    71,    85,    86,    72,
      87,    88,    89,    90,    73,    74,    91,    92,    93,    94,
      75,    95,    96,    76,    97,    77,   104,    78,    98,    99,
     100,   101,     0,    79,     0,     0,     0,     0,    80,     0,
       0,   105,   106,   107,   108,   109,   110,    -2,     1,     0,
       0,     0,     0,     2,     0,     0,     0,     0,     3,     4,
       0,     0,     0,     0,     5,     6,     0,     7,     8,     9,
      10,     0,     0,    11,    12,    13,    14,     0,    15,    16,
       0,    17,     0,    18,     0,    19,    20,    21,    22,    23,
       1,    24,    25,    26,    27,     2,    28,    29,    30,     0,
       3,     4,     0,     0,     0,     0,     5,     6,     0,     7,
       8,     9,    10,     0,     0,    11,    12,    13,    14,     0,
      15,    16,     0,    17,     0,    18,     0,    19,    20,    21,
      22,    23,     0,    24,    25,    26,    27,     0,    28,    29,
      30,    36,    37,    38,    39,    40,    41,    42,    43,    44,
       0,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,    60,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128
};

static const yytype_int8 yycheck[] =
{
       1,     1,     3,     0,    32,     4,     4,     7,     8,     9,
      10,     5,     5,    13,    14,    15,    16,     5,     5,    19,
       5,     5,     5,     5,    24,    25,     5,     5,     5,     5,
      30,     5,     5,    33,     5,    35,    37,    37,     5,     5,
       5,    82,    -1,    43,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    52,    53,    54,    55,    56,    57,     0,     1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    -1,    17,    18,    -1,    20,    21,    22,
      23,    -1,    -1,    26,    27,    28,    29,    -1,    31,    32,
      -1,    34,    -1,    36,    -1,    38,    39,    40,    41,    42,
       1,    44,    45,    46,    47,     6,    49,    50,    51,    -1,
      11,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,    20,
      21,    22,    23,    -1,    -1,    26,    27,    28,    29,    -1,
      31,    32,    -1,    34,    -1,    36,    -1,    38,    39,    40,
      41,    42,    -1,    44,    45,    46,    47,    -1,    49,    50,
      51,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    28,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100
};

  /* YYSTOSSTATE-NUM -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     6,    11,    12,    17,    18,    20,    21,    22,
      23,    26,    27,    28,    29,    31,    32,    34,    36,    38,
      39,    40,    41,    42,    44,    45,    46,    47,    49,    50,
      51,    59,    60,    61,     4,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,     0,    61,     1,     7,     8,     9,    10,    13,    14,
      15,    16,    19,    24,    25,    30,    33,    35,    37,    43,
      48,    63,     4,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,    63,     1,     3,    37,    52,    53,    54,    55,    56,
      57,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64
};

  /* YYR1YYN -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64
};

  /* YYR2YYN -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     2,     2,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize;

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yynerrs = 0;
  yystate = 0;
  yyerrstatus = 0;

  yystacksize = YYINITDEPTH;
  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;


  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 98 "sintactico.yy"
                   { raiz = (yyval.nodito); }
#line 1732 "parser.cpp"
    break;

  case 3:
#line 102 "sintactico.yy"
        {
            (yyval.nodito)=(yyvsp[-1].nodito);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1741 "parser.cpp"
    break;

  case 4:
#line 107 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,-1);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1750 "parser.cpp"
    break;

  case 5:
#line 114 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,0);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1759 "parser.cpp"
    break;

  case 6:
#line 119 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,5);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1768 "parser.cpp"
    break;

  case 7:
#line 124 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,6);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1777 "parser.cpp"
    break;

  case 8:
#line 129 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,11);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1786 "parser.cpp"
    break;

  case 9:
#line 134 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,12);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1795 "parser.cpp"
    break;

  case 10:
#line 139 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,14);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1804 "parser.cpp"
    break;

  case 11:
#line 144 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,15);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1813 "parser.cpp"
    break;

  case 12:
#line 149 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,31);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1822 "parser.cpp"
    break;

  case 13:
#line 154 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,32);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1831 "parser.cpp"
    break;

  case 14:
#line 159 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,33);
        }
#line 1839 "parser.cpp"
    break;

  case 15:
#line 163 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,34);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1848 "parser.cpp"
    break;

  case 16:
#line 168 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,35);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1857 "parser.cpp"
    break;

  case 17:
#line 173 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,36);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1866 "parser.cpp"
    break;

  case 18:
#line 178 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,37);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1875 "parser.cpp"
    break;

  case 19:
#line 183 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,38);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1884 "parser.cpp"
    break;

  case 20:
#line 188 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,39);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1893 "parser.cpp"
    break;

  case 21:
#line 193 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,40);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1902 "parser.cpp"
    break;

  case 22:
#line 198 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,41);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1911 "parser.cpp"
    break;

  case 23:
#line 203 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,42);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1920 "parser.cpp"
    break;

  case 24:
#line 208 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,43);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1929 "parser.cpp"
    break;

  case 25:
#line 213 "sintactico.yy"
        {
           (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,44);
           (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1938 "parser.cpp"
    break;

  case 26:
#line 218 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,45);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1947 "parser.cpp"
    break;

  case 27:
#line 223 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,46);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1956 "parser.cpp"
    break;

  case 28:
#line 228 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,47);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1965 "parser.cpp"
    break;

  case 29:
#line 233 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,48);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 1974 "parser.cpp"
    break;

  case 30:
#line 238 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,49);
        }
#line 1982 "parser.cpp"
    break;

  case 31:
#line 242 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,63);
        }
#line 1990 "parser.cpp"
    break;

  case 32:
#line 246 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,64);
        }
#line 1998 "parser.cpp"
    break;

  case 33:
#line 250 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,51);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2007 "parser.cpp"
    break;

  case 34:
#line 255 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,-3);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2016 "parser.cpp"
    break;

  case 35:
#line 262 "sintactico.yy"
        {
            (yyval.nodito)=(yyvsp[-2].nodito);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2025 "parser.cpp"
    break;

  case 36:
#line 267 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-1]).first_line, (yylsp[-1]).first_column,-2);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2034 "parser.cpp"
    break;

  case 37:
#line 274 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,1);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2043 "parser.cpp"
    break;

  case 38:
#line 279 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,2);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2052 "parser.cpp"
    break;

  case 39:
#line 284 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,3);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2061 "parser.cpp"
    break;

  case 40:
#line 289 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,4);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2070 "parser.cpp"
    break;

  case 41:
#line 294 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,7);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2079 "parser.cpp"
    break;

  case 42:
#line 299 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,9);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2088 "parser.cpp"
    break;

  case 43:
#line 304 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,10);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2097 "parser.cpp"
    break;

  case 44:
#line 309 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,8);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2106 "parser.cpp"
    break;

  case 45:
#line 314 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,13);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2115 "parser.cpp"
    break;

  case 46:
#line 319 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,55);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2124 "parser.cpp"
    break;

  case 47:
#line 324 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,56);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2133 "parser.cpp"
    break;

  case 48:
#line 329 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,57);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2142 "parser.cpp"
    break;

  case 49:
#line 334 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,58);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2151 "parser.cpp"
    break;

  case 50:
#line 339 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,59);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2160 "parser.cpp"
    break;

  case 51:
#line 344 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,60);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2169 "parser.cpp"
    break;

  case 52:
#line 349 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,61);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2178 "parser.cpp"
    break;

  case 53:
#line 354 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,62);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2187 "parser.cpp"
    break;

  case 54:
#line 359 "sintactico.yy"
        {
            (yyval.nodito) = new Nodo((yylsp[-2]).first_line, (yylsp[-2]).first_column,-3);
            (yyval.nodito)->agregar(*(yyvsp[0].nodito));
        }
#line 2196 "parser.cpp"
    break;

  case 55:
#line 366 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,23,(yyvsp[0].TEXT));
    }
#line 2204 "parser.cpp"
    break;

  case 56:
#line 370 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,24,(yyvsp[0].TEXT));
    }
#line 2212 "parser.cpp"
    break;

  case 57:
#line 374 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,25,(yyvsp[0].TEXT));
    }
#line 2220 "parser.cpp"
    break;

  case 58:
#line 378 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,26,(yyvsp[0].TEXT));
    }
#line 2228 "parser.cpp"
    break;

  case 59:
#line 382 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,23,(yyvsp[0].TEXT));
    }
#line 2236 "parser.cpp"
    break;

  case 60:
#line 386 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,24,(yyvsp[0].TEXT));
    }
#line 2244 "parser.cpp"
    break;

  case 61:
#line 390 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,65,(yyvsp[0].TEXT));
    }
#line 2252 "parser.cpp"
    break;

  case 62:
#line 394 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,24,(yyvsp[0].TEXT));
    }
#line 2260 "parser.cpp"
    break;

  case 63:
#line 398 "sintactico.yy"
    {
        (yyval.nodito) = new Nodo((yylsp[0]).first_line, (yylsp[0]).first_column,-3);
    }
#line 2268 "parser.cpp"
    break;


#line 2272 "parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 403 "sintactico.yy"

