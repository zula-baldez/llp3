/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"

    #include <stdio.h>
    #include <math.h>
    #include <stdbool.h>
    #include "ast.h"
    extern void yyerror (char const *);
    extern int yylex(void);

    #ifdef YYDEBUG
      yydebug = 1;
    #endif

#line 84 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"

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

#include "grammar.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_CREATE_TABLE = 3,             /* "CREATE_TABLE"  */
  YYSYMBOL_T_DROP_TABLE = 4,               /* "DROP_TABLE"  */
  YYSYMBOL_T_FOR = 5,                      /* "FOR"  */
  YYSYMBOL_T_FILTER = 6,                   /* "FILTER"  */
  YYSYMBOL_T_RETURN = 7,                   /* "RETURN"  */
  YYSYMBOL_T_REMOVE = 8,                   /* "REMOVE"  */
  YYSYMBOL_T_INSERT = 9,                   /* "INSERT"  */
  YYSYMBOL_T_UPDATE = 10,                  /* "UPDATE"  */
  YYSYMBOL_T_IN = 11,                      /* "IN"  */
  YYSYMBOL_T_QUOTED_STRING = 12,           /* "q-string"  */
  YYSYMBOL_T_NULL = 13,                    /* "null"  */
  YYSYMBOL_T_TRUE = 14,                    /* "true"  */
  YYSYMBOL_T_FALSE = 15,                   /* "false"  */
  YYSYMBOL_T_STRING = 16,                  /* "string"  */
  YYSYMBOL_T_INTEGER = 17,                 /* "int"  */
  YYSYMBOL_T_DOUBLE = 18,                  /* "double"  */
  YYSYMBOL_T_EQ = 19,                      /* "=="  */
  YYSYMBOL_T_NE = 20,                      /* "!="  */
  YYSYMBOL_T_LT = 21,                      /* "<"  */
  YYSYMBOL_T_GT = 22,                      /* ">"  */
  YYSYMBOL_T_LE = 23,                      /* "<="  */
  YYSYMBOL_T_GE = 24,                      /* ">="  */
  YYSYMBOL_T_COMMA = 25,                   /* ","  */
  YYSYMBOL_T_OPEN = 26,                    /* "("  */
  YYSYMBOL_T_CLOSE = 27,                   /* ")"  */
  YYSYMBOL_T_OBJECT_OPEN = 28,             /* "{"  */
  YYSYMBOL_T_OBJECT_CLOSE = 29,            /* "}"  */
  YYSYMBOL_T_COLON = 30,                   /* ":"  */
  YYSYMBOL_T_NOT = 31,                     /* "not operator"  */
  YYSYMBOL_T_AND = 32,                     /* "and operator"  */
  YYSYMBOL_T_OR = 33,                      /* "or operator"  */
  YYSYMBOL_T_CONTAINS = 34,                /* "contains function"  */
  YYSYMBOL_35_ = 35,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_queryStart = 37,                /* queryStart  */
  YYSYMBOL_create_table_statement = 38,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 39,      /* drop_table_statement  */
  YYSYMBOL_column_list = 40,               /* column_list  */
  YYSYMBOL_column = 41,                    /* column  */
  YYSYMBOL_query = 42,                     /* query  */
  YYSYMBOL_final_statement = 43,           /* final_statement  */
  YYSYMBOL_optional_statement_block_statements = 44, /* optional_statement_block_statements  */
  YYSYMBOL_statement_block_statement = 45, /* statement_block_statement  */
  YYSYMBOL_for_output_variable = 46,       /* for_output_variable  */
  YYSYMBOL_for_statement = 47,             /* for_statement  */
  YYSYMBOL_filter_statement = 48,          /* filter_statement  */
  YYSYMBOL_return_statement = 49,          /* return_statement  */
  YYSYMBOL_in_collection = 50,             /* in_collection  */
  YYSYMBOL_remove_statement = 51,          /* remove_statement  */
  YYSYMBOL_insert_statement = 52,          /* insert_statement  */
  YYSYMBOL_update_parameters = 53,         /* update_parameters  */
  YYSYMBOL_update_statement = 54,          /* update_statement  */
  YYSYMBOL_object = 55,                    /* object  */
  YYSYMBOL_56_1 = 56,                      /* $@1  */
  YYSYMBOL_optional_object_elements = 57,  /* optional_object_elements  */
  YYSYMBOL_object_elements_list = 58,      /* object_elements_list  */
  YYSYMBOL_object_element = 59,            /* object_element  */
  YYSYMBOL_object_element_name = 60,       /* object_element_name  */
  YYSYMBOL_operator_binary = 61,           /* operator_binary  */
  YYSYMBOL_contains = 62,                  /* contains  */
  YYSYMBOL_expression = 63,                /* expression  */
  YYSYMBOL_reference = 64,                 /* reference  */
  YYSYMBOL_numeric_value = 65,             /* numeric_value  */
  YYSYMBOL_value_literal = 66,             /* value_literal  */
  YYSYMBOL_in_collection_name = 67,        /* in_collection_name  */
  YYSYMBOL_variable_name = 68              /* variable_name  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
       2,     2,     2,     2,     2,     2,    35,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   102,   102,   105,   108,   114,   123,   131,   138,   147,
     158,   166,   168,   170,   172,   177,   179,   184,   186,   188,
     190,   192,   197,   204,   213,   221,   228,   234,   241,   248,
     255,   261,   261,   270,   272,   274,   279,   281,   286,   296,
     305,   308,   313,   323,   333,   345,   357,   367,   377,   387,
     398,   405,   420,   423,   426,   429,   440,   453,   459,   462,
     472,   475,   481,   484,   487,   490,   493,   499,   506
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
  "\"end\"", "error", "\"invalid token\"", "\"CREATE_TABLE\"",
  "\"DROP_TABLE\"", "\"FOR\"", "\"FILTER\"", "\"RETURN\"", "\"REMOVE\"",
  "\"INSERT\"", "\"UPDATE\"", "\"IN\"", "\"q-string\"", "\"null\"",
  "\"true\"", "\"false\"", "\"string\"", "\"int\"", "\"double\"", "\"==\"",
  "\"!=\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\",\"", "\"(\"",
  "\")\"", "\"{\"", "\"}\"", "\":\"", "\"not operator\"",
  "\"and operator\"", "\"or operator\"", "\"contains function\"", "'.'",
  "$accept", "queryStart", "create_table_statement",
  "drop_table_statement", "column_list", "column", "query",
  "final_statement", "optional_statement_block_statements",
  "statement_block_statement", "for_output_variable", "for_statement",
  "filter_statement", "return_statement", "in_collection",
  "remove_statement", "insert_statement", "update_parameters",
  "update_statement", "object", "$@1", "optional_object_elements",
  "object_elements_list", "object_element", "object_element_name",
  "operator_binary", "contains", "expression", "reference",
  "numeric_value", "value_literal", "in_collection_name", "variable_name", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-31)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-68)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      60,    10,    12,    23,   -31,   -31,   -31,     7,     9,   -31,
     -31,    25,    -7,    -7,    -7,    -7,    -7,   -31,   -31,   -31,
     -31,   -31,    39,    46,    65,    50,   -31,    56,   -31,   -31,
     -31,   -31,   -31,   -31,   -31,   -31,    -7,   -31,    42,   -31,
     -31,   -31,    89,    41,   -31,   -31,    89,   104,   104,   -31,
     104,    57,     0,   -31,    -7,    11,    24,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    70,    43,   -31,
     -31,   -31,    83,    50,   -31,    89,   -31,   -31,    72,    61,
      78,   -31,    75,    59,    89,    51,    51,    93,    93,    93,
      93,   133,   119,   -31,   158,   -31,   -31,   -31,   -31,    24,
      -7,    -7,   -31,    89,    74,   -31
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      15,     0,     0,     0,     2,     3,     4,     0,     0,     6,
       1,     0,     0,     0,     0,     0,     0,    10,    16,    17,
      18,    11,    19,    20,    21,     0,    68,     0,    22,    62,
      64,    65,    66,    56,    60,    61,     0,    31,     0,    59,
      52,    55,    24,    54,    63,    53,    25,     0,     0,    30,
       0,     0,     0,     7,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      28,    29,     0,     0,     5,    23,    58,    41,    38,     0,
      34,    36,     0,     0,    50,    44,    45,    46,    47,    48,
      49,    43,    42,    57,    56,    26,     9,     8,    32,    35,
       0,     0,    37,    39,     0,    51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,   -31,   -31,   -31,   -31,    44,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -30,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,    15,   -31,   -31,   -31,   -12,   -31,   -31,
     -31,   -31,   -31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    52,    53,     6,    17,     7,    18,
      27,    19,    20,    21,    69,    22,    23,    49,    24,    39,
      56,    79,    80,    81,    82,    40,    41,    84,    43,    44,
      45,    95,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      42,    46,    47,    48,    50,    29,    30,    31,    32,    33,
      34,    35,    11,    12,    13,    14,    15,    16,    70,    36,
      71,    37,    58,    10,    55,    73,     8,    38,     9,    74,
      59,    60,    61,    62,    63,    64,    77,    25,    76,   -12,
      78,    26,    75,    65,    66,    83,   -13,    85,    86,    87,
      88,    89,    90,    91,    92,    29,    30,    31,    32,    94,
      34,    35,    58,     1,     2,   -14,    51,    54,    57,    36,
      58,    37,    61,    62,    63,    64,    67,    38,    59,    60,
      61,    62,    63,    64,   101,    58,    93,    72,   103,   104,
      98,    65,    66,    59,    60,    61,    62,    63,    64,    96,
      58,   105,   -40,    99,    58,   100,    65,    66,    59,    60,
      61,    62,    63,    64,   102,    68,     0,    97,     0,     0,
       0,    65,    66,    59,    60,    61,    62,    63,    64,     0,
      58,     0,     0,     0,     0,     0,    65,    66,    59,    60,
      61,    62,    63,    64,    58,     0,     0,     0,     0,     0,
       0,    65,    59,    60,    61,    62,    63,    64,   -67,     0,
       0,     0,     0,   -67,   -67,   -67,   -67,   -67,   -67
};

static const yytype_int8 yycheck[] =
{
      12,    13,    14,    15,    16,    12,    13,    14,    15,    16,
      17,    18,     5,     6,     7,     8,     9,    10,    48,    26,
      50,    28,    11,     0,    36,    25,    16,    34,    16,    29,
      19,    20,    21,    22,    23,    24,    12,    28,    27,     0,
      16,    16,    54,    32,    33,    57,     0,    59,    60,    61,
      62,    63,    64,    65,    66,    12,    13,    14,    15,    16,
      17,    18,    11,     3,     4,     0,    16,    11,    26,    26,
      11,    28,    21,    22,    23,    24,    35,    34,    19,    20,
      21,    22,    23,    24,    25,    11,    16,    30,   100,   101,
      29,    32,    33,    19,    20,    21,    22,    23,    24,    16,
      11,    27,    30,    25,    11,    30,    32,    33,    19,    20,
      21,    22,    23,    24,    99,    11,    -1,    73,    -1,    -1,
      -1,    32,    33,    19,    20,    21,    22,    23,    24,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    32,    33,    19,    20,
      21,    22,    23,    24,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    19,    20,    21,    22,    23,    24,     0,    -1,
      -1,    -1,    -1,     5,     6,     7,     8,     9,    10
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    37,    38,    39,    42,    44,    16,    16,
       0,     5,     6,     7,     8,     9,    10,    43,    45,    47,
      48,    49,    51,    52,    54,    28,    16,    46,    68,    12,
      13,    14,    15,    16,    17,    18,    26,    28,    34,    55,
      61,    62,    63,    64,    65,    66,    63,    63,    63,    53,
      63,    16,    40,    41,    11,    63,    56,    26,    11,    19,
      20,    21,    22,    23,    24,    32,    33,    35,    11,    50,
      50,    50,    30,    25,    29,    63,    27,    12,    16,    57,
      58,    59,    60,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    16,    16,    67,    16,    41,    29,    25,
      30,    25,    59,    63,    63,    27
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    37,    37,    38,    39,    40,    40,    41,
      42,    43,    43,    43,    43,    44,    44,    45,    45,    45,
      45,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    56,    55,    57,    57,    57,    58,    58,    59,    59,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    62,    63,    63,    63,    63,    64,    64,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    67,    68
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     5,     2,     1,     3,     3,
       2,     1,     1,     1,     1,     0,     2,     1,     1,     1,
       1,     1,     1,     4,     2,     2,     2,     3,     3,     2,
       2,     0,     4,     0,     1,     2,     1,     3,     1,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     6,     1,     1,     1,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  if (yychar <= T_END)
    {
      yychar = T_END;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* queryStart: create_table_statement  */
#line 102 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                           {
        // handle create table statement
    }
#line 1501 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 3: /* queryStart: drop_table_statement  */
#line 105 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                         {
        // handle drop table statement
    }
#line 1509 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 4: /* queryStart: query  */
#line 108 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
          {

    }
#line 1517 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 5: /* create_table_statement: "CREATE_TABLE" "string" "{" column_list "}"  */
#line 114 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                                                     {
        struct AstNode* tableNameNode = createNodeDataSource((yyvsp[-3].s_val));
        struct AstNode* tableFieldsNode = (struct AstNode*)((yyvsp[-1].node));
        struct AstNode* createTableNode = createNodeCreateTable(tableNameNode, tableFieldsNode);
        addOperation(getCurrScope(), createTableNode);
    }
#line 1528 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 6: /* drop_table_statement: "DROP_TABLE" "string"  */
#line 123 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                          {
        struct AstNode* tableNameNode = createNodeValueString((yyvsp[0].s_val));
        struct AstNode* dropTableNode = createNodeDropTable(tableNameNode);
        addOperation(getCurrScope(), dropTableNode);
    }
#line 1538 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 7: /* column_list: column  */
#line 131 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
           {
        struct AstNode* col = (struct AstNode*)((yyvsp[0].node));
        struct AstNode* columnListNode = createNodeColumnList();
        addOperation(columnListNode, col);
        (yyval.node) = columnListNode;

    }
#line 1550 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 8: /* column_list: column_list "," column  */
#line 138 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
        struct AstNode* columnListNode = (struct AstNode*)((yyvsp[-2].node));
        struct AstNode* columnNode = (struct AstNode*)((yyvsp[0].node));
        addOperation(columnListNode, columnNode);
        (yyval.node) = columnListNode;
    }
#line 1561 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 9: /* column: "string" ":" "string"  */
#line 147 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                              {
        // attribute-name : attribute-type
        struct AstNode* fieldNameNode = createNodeValueString((yyvsp[-2].s_val));
        struct AstNode* fieldTypeNode = createNodeValueString((yyvsp[0].s_val));
        struct AstNode* tableFieldNode = createNodeTableField(fieldNameNode, fieldTypeNode);
        (yyval.node) = tableFieldNode;
    }
#line 1573 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 10: /* query: optional_statement_block_statements final_statement  */
#line 158 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                                        {
    }
#line 1580 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 11: /* final_statement: return_statement  */
#line 166 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                     {
    }
#line 1587 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 12: /* final_statement: remove_statement  */
#line 168 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                     {
    }
#line 1594 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 13: /* final_statement: insert_statement  */
#line 170 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                     {
    }
#line 1601 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 14: /* final_statement: update_statement  */
#line 172 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                     {
    }
#line 1608 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 15: /* optional_statement_block_statements: %empty  */
#line 177 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                {
    }
#line 1615 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 16: /* optional_statement_block_statements: optional_statement_block_statements statement_block_statement  */
#line 179 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                                                  {
    }
#line 1622 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 17: /* statement_block_statement: for_statement  */
#line 184 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                  {
    }
#line 1629 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 18: /* statement_block_statement: filter_statement  */
#line 186 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                     {
    }
#line 1636 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 19: /* statement_block_statement: remove_statement  */
#line 188 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                      {
    }
#line 1643 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 20: /* statement_block_statement: insert_statement  */
#line 190 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                     {
    }
#line 1650 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 21: /* statement_block_statement: update_statement  */
#line 192 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                     {
    }
#line 1657 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 22: /* for_output_variable: variable_name  */
#line 197 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                  {
          struct AstNode* node = createNodeValueString((yyvsp[0].s_val));
          (yyval.node) = node;
        }
#line 1666 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 23: /* for_statement: "FOR" for_output_variable "IN" expression  */
#line 204 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                              {
        struct AstNode* variableNameNode = (struct AstNode*)((yyvsp[-2].node));
        struct AstNode* variableNode = createNodeVariable(variableNameNode->astNodeValue._string);
        addVariable(variableNameNode->astNodeValue._string, variableNode);
        addOperation(getCurrScope(), createNodeFor(variableNode, (yyvsp[0].node)));
    }
#line 1677 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 24: /* filter_statement: "FILTER" expression  */
#line 213 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                        {
      struct AstNode* filterNode = createNodeFilter((yyvsp[0].node));
      addOperation(getCurrScope(), filterNode);

    }
#line 1687 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 25: /* return_statement: "RETURN" expression  */
#line 221 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                        {
      struct AstNode* node = createNodeReturn((yyvsp[0].node));
      addOperation(getCurrScope(), node);
    }
#line 1696 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 26: /* in_collection: "IN" in_collection_name  */
#line 228 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                            {
      (yyval.node) = (yyvsp[0].node);
    }
#line 1704 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 27: /* remove_statement: "REMOVE" expression in_collection  */
#line 234 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                       {
      struct AstNode* node = createNodeRemove((yyvsp[-1].node), (yyvsp[0].node));
      addOperation(getCurrScope(), node);
    }
#line 1713 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 28: /* insert_statement: "INSERT" expression in_collection  */
#line 241 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                      {
      struct AstNode* node = createNodeInsert((yyvsp[-1].node), (yyvsp[0].node));
      addOperation(getCurrScope(), node);
    }
#line 1722 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 29: /* update_parameters: expression in_collection  */
#line 248 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                             {
      struct AstNode* node = createNodeUpdate((yyvsp[-1].node), (yyvsp[0].node));
      addOperation(getCurrScope(), node);
    }
#line 1731 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 30: /* update_statement: "UPDATE" update_parameters  */
#line 255 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
    }
#line 1738 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 31: /* $@1: %empty  */
#line 261 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                  {
      struct AstNode* node = createNodeObject();
      pushCommon(node);
    }
#line 1747 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 32: /* object: "{" $@1 optional_object_elements "}"  */
#line 264 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                              {
      (yyval.node) = (struct AstNode*)(popCommon());
    }
#line 1755 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 33: /* optional_object_elements: %empty  */
#line 270 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                {
    }
#line 1762 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 34: /* optional_object_elements: object_elements_list  */
#line 272 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                         {
    }
#line 1769 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 35: /* optional_object_elements: object_elements_list ","  */
#line 274 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                 {
    }
#line 1776 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 36: /* object_elements_list: object_element  */
#line 279 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                   {
    }
#line 1783 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 37: /* object_elements_list: object_elements_list "," object_element  */
#line 281 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                                {
    }
#line 1790 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 38: /* object_element: "string"  */
#line 286 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
             {
      // attribute-name-only e.g. { foo, bar }
      struct AstNode* variable = getVariable((yyvsp[0].s_val));
      if (variable != NULL) {
        yyerror("variable used by object does not exists");
      }
      struct AstNode* node = createNodeReference(variable->astNodeValue._string);
      pushObjectElement((yyvsp[0].s_val), node);
      (yyval.node) = node;
    }
#line 1805 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 39: /* object_element: object_element_name ":" expression  */
#line 296 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                           {
      struct AstNode* value = (struct AstNode*)((yyvsp[0].node));
      // attribute-name : attribute-value
      pushObjectElement((yyvsp[-2].s_val), (yyvsp[0].node));
    }
#line 1815 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 40: /* object_element_name: "string"  */
#line 305 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
             {
      (yyval.s_val) = ((yyvsp[0].s_val));
    }
#line 1823 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 41: /* object_element_name: "q-string"  */
#line 308 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                    {
      (yyval.s_val) = ((yyvsp[0].s_val));
    }
#line 1831 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 42: /* operator_binary: expression "or operator" expression  */
#line 313 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
      struct AstNode* left = (struct AstNode*)((yyvsp[-2].node));
      struct AstNode* right = (struct AstNode*)((yyvsp[0].node));

      if(left->astNodeType == NODE_TYPE_VARIABLE && left->astNodeValue.type != BOOL_TYPE ||
        right->astNodeType == NODE_TYPE_VARIABLE && right->astNodeValue.type != BOOL_TYPE) {
          yyerror("wrong OR operands");
      }
      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_OR, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1846 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 43: /* operator_binary: expression "and operator" expression  */
#line 323 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                {
      struct AstNode* left = (struct AstNode*)((yyvsp[-2].node));
      struct AstNode* right = (struct AstNode*)((yyvsp[0].node));

      if(left->astNodeType == NODE_TYPE_VARIABLE && left->astNodeValue.type != BOOL_TYPE ||
        right->astNodeType == NODE_TYPE_VARIABLE && right->astNodeValue.type != BOOL_TYPE) {
          yyerror("wrong AND operands");
      }
      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_AND, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1861 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 44: /* operator_binary: expression "==" expression  */
#line 333 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
      struct AstNode* left = (struct AstNode*)((yyvsp[-2].node));
      struct AstNode* right = (struct AstNode*)((yyvsp[0].node));

      if(left->astNodeType == NODE_TYPE_VARIABLE && right->astNodeType == NODE_TYPE_VARIABLE
          && left->astNodeValue.type != right->astNodeValue.type
        ) {
          yyerror("wrong EQ operands");
      }

      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_EQ, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1878 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 45: /* operator_binary: expression "!=" expression  */
#line 345 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
      struct AstNode* left = (struct AstNode*)((yyvsp[-2].node));
      struct AstNode* right = (struct AstNode*)((yyvsp[0].node));

      if(left->astNodeType == NODE_TYPE_VARIABLE && right->astNodeType == NODE_TYPE_VARIABLE
          && left->astNodeValue.type != right->astNodeValue.type
        ) {
          yyerror("wrong NE operands");
      }

      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_NE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1895 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 46: /* operator_binary: expression "<" expression  */
#line 357 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
      struct AstNode* left = (struct AstNode*)((yyvsp[-2].node));
      struct AstNode* right = (struct AstNode*)((yyvsp[0].node));

      if(left->astNodeType == NODE_TYPE_VARIABLE && left->astNodeValue.type != INT_TYPE ||
        right->astNodeType == NODE_TYPE_VARIABLE && right->astNodeValue.type != INT_TYPE) {
          yyerror("wrong T_LT operands");
      }
      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_LT, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1910 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 47: /* operator_binary: expression ">" expression  */
#line 367 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
      struct AstNode* left = (struct AstNode*)((yyvsp[-2].node));
      struct AstNode* right = (struct AstNode*)((yyvsp[0].node));

      if(left->astNodeType == NODE_TYPE_VARIABLE && left->astNodeValue.type != INT_TYPE ||
        right->astNodeType == NODE_TYPE_VARIABLE && right->astNodeValue.type != INT_TYPE) {
          yyerror("wrong T_GT operands");
      }
      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_GT, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1925 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 48: /* operator_binary: expression "<=" expression  */
#line 377 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
      struct AstNode* left = (struct AstNode*)((yyvsp[-2].node));
      struct AstNode* right = (struct AstNode*)((yyvsp[0].node));

      if(left->astNodeType == NODE_TYPE_VARIABLE && left->astNodeValue.type != INT_TYPE ||
        right->astNodeType == NODE_TYPE_VARIABLE && right->astNodeValue.type != INT_TYPE) {
          yyerror("wrong T_LE operands");
      }
      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_LE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1940 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 49: /* operator_binary: expression ">=" expression  */
#line 387 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_GE, (yyvsp[-2].node), (yyvsp[0].node));

      struct AstNode* left = (struct AstNode*)((yyvsp[-2].node));
      struct AstNode* right = (struct AstNode*)((yyvsp[0].node));

      if(left->astNodeType == NODE_TYPE_VARIABLE && left->astNodeValue.type != INT_TYPE ||
        right->astNodeType == NODE_TYPE_VARIABLE && right->astNodeValue.type != INT_TYPE) {
          yyerror("wrong T_GE operands");
      }
    }
#line 1956 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 50: /* operator_binary: expression "IN" expression  */
#line 398 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                               {
      (yyval.node) = createNodeBinaryOperator(NODE_TYPE_OPERATOR_BINARY_IN, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1964 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 51: /* contains: "contains function" "(" expression "," expression ")"  */
#line 405 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                                          {
    struct AstNode* left = (struct AstNode*)((yyvsp[-3].node));
    struct AstNode* right = (struct AstNode*)((yyvsp[-1].node));
    if(((left->astNodeType == NODE_TYPE_VARIABLE && left->astNodeValue.type == STRING_TYPE) || left->astNodeType == NODE_TYPE_REFERENCE) ||
      ((right->astNodeType == NODE_TYPE_VARIABLE && right->astNodeValue.type == STRING_TYPE) || right->astNodeType == NODE_TYPE_REFERENCE)
    ) {
      struct AstNode* containsNode = createNodeContains(left, right);
      (yyval.node) = containsNode;
    } else {
        yyerror("wrong contains expression");
    }
  }
#line 1981 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 52: /* expression: operator_binary  */
#line 420 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                 {
      (yyval.node) = (yyvsp[0].node);
    }
#line 1989 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 53: /* expression: value_literal  */
#line 423 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1997 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 54: /* expression: reference  */
#line 426 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
              {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2005 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 55: /* expression: contains  */
#line 429 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
             {
    (yyval.node) = (yyvsp[0].node);
  }
#line 2013 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 56: /* reference: "string"  */
#line 440 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
             {
      // variable or collection or view
      struct AstNode* node = NULL;
      void* variable = NULL;

      variable = getVariable((yyvsp[0].s_val));
      if (variable == NULL) {
          node = createNodeDataSource((yyvsp[0].s_val));
      } else {
        node = variable;
      }
      (yyval.node) = node;
    }
#line 2031 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 57: /* reference: reference '.' "string"  */
#line 453 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                             {
        struct AstNode* ref = (struct AstNode*)((yyvsp[-2].node));
        struct AstNode* access = createNodeAttributeAccess((yyvsp[0].s_val));
        addOperation(ref, access);
        (yyval.node) = ref;
    }
#line 2042 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 58: /* reference: "(" expression ")"  */
#line 459 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                                {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2050 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 59: /* reference: object  */
#line 462 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
             {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2058 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 60: /* numeric_value: "int"  */
#line 472 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
              {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2066 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 61: /* numeric_value: "double"  */
#line 475 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
             {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2074 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 62: /* value_literal: "q-string"  */
#line 481 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                    {
      (yyval.node) = createNodeValueString((yyvsp[0].s_val));
    }
#line 2082 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 63: /* value_literal: numeric_value  */
#line 484 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
                  {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2090 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 64: /* value_literal: "null"  */
#line 487 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
           {
      (yyval.node) = createNodeValueNull();
    }
#line 2098 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 65: /* value_literal: "true"  */
#line 490 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
           {
      (yyval.node) = createNodeValueBool(true);
    }
#line 2106 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 66: /* value_literal: "false"  */
#line 493 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
            {
      (yyval.node) = createNodeValueBool(false);
    }
#line 2114 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 67: /* in_collection_name: "string"  */
#line 499 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
             {
      (yyval.node) = createNodeDataSource((yyvsp[0].s_val));
    }
#line 2122 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;

  case 68: /* variable_name: "string"  */
#line 506 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"
             {
      (yyval.s_val) = ((yyvsp[0].s_val));
    }
#line 2130 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"
    break;


#line 2134 "/home/egor/CLionProjects/llp/parser/ast/grammar.c"

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
          = {yyssp, yytoken};
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
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= T_END)
        {
          /* Return failure if at end of input.  */
          if (yychar == T_END)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
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
  ++yynerrs;

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
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

#line 511 "/home/egor/CLionProjects/llp/parser/ast/grammar.y"

