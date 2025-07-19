
#include "intepreter.h"
#include <stdio.h>
#include <stdlib.h>

void init_symbol_table(void) {
    
    variable_count = 0;

    for(int i = 0; i < 100; i++)
        symbol_table[i] = NULL;

}

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

void prompt(){

    printf("\n@> ");
    fflush(stdout);

    return;
}

void mainloop(bool *run_ptr){
    int8* cmd;
    Lexer lexer;
    Token token;
    Parser* parser;
    AST* result;

    prompt();
    cmd = readline();
    if(cmd){
        if(!strcmp($c cmd, "exit")) {
            *run_ptr = false;
        } else {
            printf("Tokenizing: '%s'\n", $c cmd);
            init_lexer(&lexer, cmd);
            parser = create_parser(&lexer);
            result = parse_assignment(parser);
            
            if(result)
                printf("Parsed!");
            else
                printf("Error in Parsing!");
        }
        
        free(cmd);
        if(parser){
            free(parser->tokens);
            free(parser);
        }
        cleanup_AST(result);
    }
    return;
}

int main(int argc, char* argv[]){
    bool run;
    bool *run_ptr;
    init_symbol_table();
    run = true;
    run_ptr = &run;

    while(run){
        mainloop(run_ptr);
    }
 
    return 0;    
}