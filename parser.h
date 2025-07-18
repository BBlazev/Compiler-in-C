#include "common.h"
#include <stdbool.h>
#include <stdlib.h>

//trying to parse 'x = 5'

typedef struct Parser {

    Token* tokens;
    int current;
    int size;
    bool error;

} Parser;

Parser* create_parser(int8 input){
    Parser  *parser = (Parser*)malloc(sizeof(Parser));

    if(!parser) return NULL;



    return parser;
}