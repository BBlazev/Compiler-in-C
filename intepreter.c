#include "intepreter.h"
#include <stdio.h>
#include <stdlib.h>

Variable* make_Variable(Type type, Identifier* ident, void* value) {
    Variable* p;
    int16 size;
    
    if (!ident || !value)
        return (Variable*)0;

    size = sizeof(struct Variable);
    p = (Variable*) malloc(size);
    if(!p)
        return (Variable*)0;

    zero($1 p, size);
    p->datatype = type;
    p->name = ident;
    p->value = value;

    return p;
}

int16 length(int8* str){
    int16 n;
    int8* p;

    if(!str)
        return 0;
        
    for(n = 0, p = str; *p; n++, p++);

    return n;
}

void copy(int8* dst, int8* src, int16 size){
    int8* dptr, *sptr;
    int16 n;

    for(dptr = dst, sptr = src, n = size; n; n--, dptr++, sptr++){
        *dptr = *sptr;
    }
    *dptr = 0;
    return;
}

void zero(int8* ptr, int16 size){
    int8* p;
    int16 n;
    
    for(p = ptr, n = size; n; n--, p++){
        *p = 0;
    }
}

int8* readline(){
    int8 *p, *ret;
    int16 size;
    int8 buffer[128];  

    zero(buffer, 128);
    
    if(!fgets($c buffer, 127, stdin))
        return $1 0;

    size = length(buffer);
    if(size > 0) {
        p = buffer + size - 1;
        if(*p == '\n') {
            *p = 0;
            size--;
        }
    }

    if(!size)
        return $1 0;

    ret = $1 malloc(size + 1);  
    if(!ret)
        return $1 0;
        
    zero(ret, size + 1);
    copy(ret, buffer, size);

    return ret;
}
static Keyword keywords[] = {
    {$1 "let", 3},
    {$1 "if", 2}, 
    {$1 "else", 4},
    {$1 "while", 5},
    {$1 "for", 3},
    {$1 "return", 6},
    {$1 "true", 4},
    {$1 "false", 5},
    {$1 "exit", 4}  
};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))

void init_lexer(Lexer* lexer, int8* input) {
    lexer->input = input;
    lexer->current = input;
    lexer->line = 1;
    lexer->column = 1;
}

bool is_alpha(int8 c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool is_digit(int8 c) {
    return c >= '0' && c <= '9';
}

bool is_alnum(int8 c) {
    return is_alpha(c) || is_digit(c);
}

bool is_whitespace(int8 c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

void skip_whitespace(Lexer* lexer) {
    while(*lexer->current && is_whitespace(*lexer->current)) {
        if(*lexer->current == '\n') {
            lexer->line++;
            lexer->column = 1;
        } else {
            lexer->column++;
        }
        lexer->current++;
    }
}

bool is_keyword(int8* text, int16 length) {
    for(int i = 0; i < KEYWORD_COUNT; i++) {
        if(keywords[i].length == length) {
            bool match = true;
            for(int j = 0; j < length; j++) {
                if(text[j] != keywords[i].word[j]) {
                    match = false;
                    break;
                }
            }
            if(match) return true;
        }
    }
    return false;
}

Token make_token(TokenType type, int8* start, int16 length, int16 line, int16 column) {
    Token token;
    token.type = type;
    token.length = length;
    token.line = line;
    token.column = column;
    
    token.value = $1 malloc(length + 1);
    if(token.value) {
        copy(token.value, start, length);
        token.value[length] = 0; 
    }
    
    return token;
}

Token scan_identifier(Lexer* lexer) {
    int8* start = lexer->current;
    int16 start_column = lexer->column;
    
    while(*lexer->current && is_alnum(*lexer->current)) {
        lexer->current++;
        lexer->column++;
    }
    
    int16 length = lexer->current - start;
    TokenType type = is_keyword(start, length) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
    
    return make_token(type, start, length, lexer->line, start_column);
}

Token scan_number(Lexer* lexer) {
    int8* start = lexer->current;
    int16 start_column = lexer->column;
    
    while(*lexer->current && is_digit(*lexer->current)) {
        lexer->current++;
        lexer->column++;
    }
    
    int16 length = lexer->current - start;
    return make_token(TOKEN_NUMBER, start, length, lexer->line, start_column);
}

Token scan_string(Lexer* lexer) {
    int8* start = lexer->current;
    int16 start_column = lexer->column;
    
    lexer->current++;
    lexer->column++;
    
    while(*lexer->current && *lexer->current != '"') {
        if(*lexer->current == '\n') {
            lexer->line++;
            lexer->column = 1;
        } else {
            lexer->column++;
        }
        lexer->current++;
    }
    
    if(*lexer->current == '"') {
        lexer->current++; 
        lexer->column++;
    }
    
    int16 length = lexer->current - start;
    return make_token(TOKEN_STRING, start, length, lexer->line, start_column);
}

Token next_token(Lexer* lexer) {
    skip_whitespace(lexer);
    
    if(!*lexer->current) {
        return make_token(TOKEN_EOF, lexer->current, 0, lexer->line, lexer->column);
    }
    
    int8 c = *lexer->current;
    
    switch(c) {
        case '+':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_PLUS, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case '-':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_MINUS, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case '*':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_MULTIPLY, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case '/':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_DIVIDE, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case '(':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_LPAREN, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case ')':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_RPAREN, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case '{':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_LBRACE, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case '}':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_RBRACE, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case ';':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_SEMICOLON, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case ',':
            lexer->current++; lexer->column++;
            return make_token(TOKEN_COMMA, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        case '"':
            return scan_string(lexer);
    }
    
    if(c == '=') {
        if(lexer->current[1] == '=') {
            lexer->current += 2; lexer->column += 2;
            return make_token(TOKEN_EQUAL, lexer->current - 2, 2, lexer->line, lexer->column - 2);
        } else {
            lexer->current++; lexer->column++;
            return make_token(TOKEN_ASSIGN, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        }
    }
    
    if(c == '!') {
        if(lexer->current[1] == '=') {
            lexer->current += 2; lexer->column += 2;
            return make_token(TOKEN_NOT_EQUAL, lexer->current - 2, 2, lexer->line, lexer->column - 2);
        }
    }
    
    if(c == '<') {
        if(lexer->current[1] == '=') {
            lexer->current += 2; lexer->column += 2;
            return make_token(TOKEN_LESS_EQUAL, lexer->current - 2, 2, lexer->line, lexer->column - 2);
        } else {
            lexer->current++; lexer->column++;
            return make_token(TOKEN_LESS, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        }
    }
    
    if(c == '>') {
        if(lexer->current[1] == '=') {
            lexer->current += 2; lexer->column += 2;
            return make_token(TOKEN_GREATER_EQUAL, lexer->current - 2, 2, lexer->line, lexer->column - 2);
        } else {
            lexer->current++; lexer->column++;
            return make_token(TOKEN_GREATER, lexer->current - 1, 1, lexer->line, lexer->column - 1);
        }
    }
    
    if(is_alpha(c)) {
        return scan_identifier(lexer);
    }
    
    // Numbers
    if(is_digit(c)) {
        return scan_number(lexer);
    }
    
    lexer->current++; lexer->column++;
    return make_token(TOKEN_ERROR, lexer->current - 1, 1, lexer->line, lexer->column - 1);
}

void free_token(Token* token) {
    if(token->value) {
        free(token->value);
        token->value = $1 0;
    }
}

void print_token(Token* token) {
    int8* type_names[] = {
        $1 "EOF", $1 "IDENTIFIER", $1 "NUMBER", $1 "STRING", $1 "KEYWORD",
        $1 "PLUS", $1 "MINUS", $1 "MULTIPLY", $1 "DIVIDE", $1 "ASSIGN",
        $1 "EQUAL", $1 "NOT_EQUAL", $1 "LESS", $1 "GREATER", 
        $1 "LESS_EQUAL", $1 "GREATER_EQUAL",
        $1 "LPAREN", $1 "RPAREN", $1 "LBRACE", $1 "RBRACE",
        $1 "SEMICOLON", $1 "COMMA", $1 "ERROR"
    };
    
    printf("Token: %s, Value: '%s', Line: %d, Column: %d\n", 
           $c type_names[token->type], $c token->value, 
           token->line, token->column);
}
void prompt(){

    printf("@> ");
    fflush(stdout);

    return;

}

void mainloop(bool *cptr){
    int8* cmd;
    Lexer lexer;
    Token token;

    prompt();
    cmd = readline();
    if(cmd){
        if(!strcmp($c cmd, "exit")) {
            *cptr = false;
        } else {
            printf("Tokenizing: '%s'\n", $c cmd);
            init_lexer(&lexer, cmd);
            
            do {
                token = next_token(&lexer);
                print_token(&token);
                
                if(token.type == TOKEN_KEYWORD && 
                   !strcmp($c token.value, "exit")) {
                    *cptr = false;
                }
                
                free_token(&token);
            } while(token.type != TOKEN_EOF && *cptr);
        }
        
        free(cmd);
    }
    return;
}

int main(int argc, char* argv[]){
    int8* cmd;
    bool go;

    bool *cptr;


    go = true;
    cptr = &go;

    while(go){

        mainloop(cptr);


    }
 
    return 0;    
}