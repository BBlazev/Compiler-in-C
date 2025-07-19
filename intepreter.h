#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "parser.h"


typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef int8 Identifier;

typedef enum Type {
    Nothing,
    Int,
    Char,
    String
} Type;

typedef struct Variable{
    Type datatype;
    Identifier *name;
    void* value;
} Variable;



void mainloop(bool*);
void prompt();
void init_symbol_table(void);



Variable* make_Variable(Type, Identifier*, void*);
Variable* symbol_table[100];
int variable_count;
Variable* find_variable(char* name);
void store_variable(Variable* variable);
void evaluate_AST(AST* node);


#define newstr(p,n,v) do{\
    int8* _tmp;\
    int16 _tmp2;\
    \
    _tmp2 = length((v));\
    if(!_tmp2){\
        (p) = (Variable*) 0;\
        break;\
    }\
    \
    _tmp = $1 malloc(_tmp2 + 1);\
    if(!_tmp){\
        (p) = (Variable*) 0;\
        break;\
    }\
    \
    copy(_tmp, (v), _tmp2);\
    (p) = make_Variable(String, (n), _tmp);\
    \
    if(!(p))\
        free(_tmp);\
}while(false)

#define newvar(t,p,n,v) do {\
    t* _tmp;\
    \
    _tmp = (t*)malloc(sizeof(t));\
    if (!_tmp){\
        (p) = (Variable*)0;\
        break;\
    }\
    *_tmp = (v);\
    (p) = make_Variable(Int, (n), _tmp);\
    if(!(p))\
        free(_tmp);\
} while(false)

#define newint(p,n,v) newvar(int32, (p), (n), (v))
#define newchar(p,n,v) newvar(char,(p),(n),(v))

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char*)
#define $i (int)