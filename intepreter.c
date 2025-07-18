
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

void prompt(){

    printf("\n@> ");
    fflush(stdout);

    return;
}

void mainloop(bool *run_ptr){
    int8* cmd;
    Lexer lexer;
    Token token;

    prompt();
    cmd = readline();
    if(cmd){
        if(!strcmp($c cmd, "exit")) {
            *run_ptr = false;
        } else {
            printf("Tokenizing: '%s'\n", $c cmd);
            init_lexer(&lexer, cmd);
            
            do {
                token = next_token(&lexer);
                print_token(&token);
                
                if(token.type == TOKEN_KEYWORD && 
                   !strcmp($c token.value, "exit")) {
                    *run_ptr = false;
                }
                
                free_token(&token);
            } while(token.type != TOKEN_EOF && *run_ptr);
        }
        
        free(cmd);
    }
    return;
}

int main(int argc, char* argv[]){
    bool run;
    bool *run_ptr;

    run = true;
    run_ptr = &run;

    while(run){
        mainloop(run_ptr);
    }
 
    return 0;    
}