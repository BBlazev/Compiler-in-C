#include "common.h"
#include <stdbool.h>
#include <stdlib.h>

//trying to parse 'x = 5'

typedef struct Parser {

    Token* tokens;
    int8 current;
    int size;
    bool error;

} Parser;

Parser* create_parser(Lexer* lexer){
    Parser  *parser = (Parser*)malloc(sizeof(Parser));
    Token   *tokens = (Token*)malloc(sizeof(Token) * 50);
    
    if(!parser) return 0;
    if(!tokens) {
        free(parser);  
        return 0;
}
    int16 counter = 0;

    do
    {
        tokens[counter] = next_token(lexer);

        counter++;
    } while (tokens[counter - 1].type != TOKEN_EOF && counter < 50);
    
    parser->current = 0;
    parser->size = counter;
    parser->tokens = tokens;
    parser->error = false;

    return parser;
}

Token current_token(Parser* parser){

    Token token;
        

    token = parser->tokens[parser->current];
    return token;

}

void advance(Parser* parser){

    if(parser->tokens[parser->current].type == TOKEN_EOF)
        return;
    else
        parser->current = parser->current + 1;

}

bool match(Parser* parser, TokenType expected_type){

    if(parser->tokens[parser->current].type == expected_type){
        advance(parser);
        return true;
    }

    return false;
}

AST* parse_assignment(Parser* parser){

    Token variable = current_token(parser);
    
    if(!match(parser, TOKEN_IDENTIFIER))
        return NULL;
    Token assign = current_token(parser);

    if(!match(parser, TOKEN_ASSIGN))
        return NULL;
    Token value = current_token(parser);
    
    if(!match(parser, TOKEN_NUMBER))
        return NULL;

    int32 number = atoi((char*) value.value);
    Identifier* var = (Identifier*) variable.value;

    AST* number_node = create_number_node(number);
    AST* assignment_node = create_assignment_node(var, number_node);

    return assignment_node;


}