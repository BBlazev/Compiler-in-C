#include "common.h"
#include <memory.h>
#include <stdlib.h>

AST* create_number_node(int32 num){

    AST* node;
    node = malloc(sizeof(*node));
    if (!node)
        return 0;
    node->tag = AST_NUMBER;
    node->data.AST_NUMBER.number = num;
    return node;
}

AST* create_variable_node(Identifier* s){

    AST* node;
    node = malloc(sizeof(*node));
    if(!node)
        return 0;

    node->tag = AST_VARIABLE;
    node->data.AST_VARIABLE.name = s;
    return node;
}

AST* create_assignment_node(Identifier* variable_name, AST* expression){

    AST* node;
    node = malloc(sizeof(*node));
    if(!node)
        return 0;

    node->tag = AST_ASSIGNMENT;
    node->data.AST_ASSIGNMENT.expression = expression;
    node->data.AST_ASSIGNMENT.variable_name = variable_name;
    return node;
}

AST* create_binary_operation(AST* left, int operator_type, AST* right){


    AST* node;
    node = malloc(sizeof(*node));
    if(!node)
        return 0;
    node->tag = operator_type; 
    node->data.AST_ADD.left = left;   
    node->data.AST_ADD.right = right; 

    return node;

}

