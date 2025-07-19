
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

Variable* find_variable(char* name){

    Variable* variable;
    if(variable_count == 0) {

        return (Variable*) NULL;

    }
    for(int i = 0; i < variable_count; i++){
        if(symbol_table[i] && !strcmp($c name, $c symbol_table[i]->name)) {
            return symbol_table[i];
        }
    }
    return (Variable*)NULL;

}
bool variable_exists(char* name){
    return find_variable(name) != NULL;
}
void store_variable(Variable* variable){

    if(variable_count >= 100) {
        printf("No more space in array");
        return;
    }

    if(variable == NULL){
        printf("Variable is NULL");
        return;
    }

    if(variable_exists((char*)variable->name)){
        printf("Variable name taken");
        return;
    }

    symbol_table[variable_count] = variable;

    variable_count++;
}




void evaluate_AST(AST* node){

    switch (node->tag)
    {
    case AST_ASSIGNMENT:
        {
            Identifier* name = node->data.AST_ASSIGNMENT.variable_name;
            AST* expression = node->data.AST_ASSIGNMENT.expression;
            if(expression->tag == AST_NUMBER){
                int32 number_value = expression->data.AST_NUMBER.number;
                int32* value_ptr = (int32*)malloc(sizeof(int32));
                *value_ptr = number_value;

                Variable* var = make_Variable(Int,name,value_ptr);
                store_variable(var);
            }
        }
        break;
    case AST_VARIABLE:
        {
            Identifier* var_name = node->data.AST_VARIABLE.name;
            Variable* var = find_variable((char*)var_name);

            if(var)
                printf("Variable %s = %d\n", $c var->name, *(int32*)var->value);
            else
                printf("Variable not found");
            break;
        }
    case AST_NUMBER:
        printf("Number: %d\n", node->data.AST_NUMBER.number);
            break;

    default:
        break;
    }
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
            
            if(result){
                evaluate_AST(result);
                printf("Parsed!");
            }
            else
            {
                parser->current = 0;
                result = parse_variable_lookup(parser);
                if(result)
                    evaluate_AST(result);
                else
                    printf("error in parsing");
            }
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