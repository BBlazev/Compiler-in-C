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
    int8 buffer[128];  // Fixed: was int* buffer[128] - wrong type!

    // Clear the buffer
    zero(buffer, 128);
    
    // Use fgets instead of read for better portability
    if(!fgets($c buffer, 127, stdin))
        return $1 0;

    // Find the length and remove newline if present
    size = length(buffer);
    if(size > 0) {
        p = buffer + size - 1;
        if(*p == '\n') {
            *p = 0;
            size--;
        }
    }

    // Check if we got any input
    if(!size)
        return $1 0;

    // Allocate memory for return string
    ret = $1 malloc(size + 1);  // Fixed: was malloc($1 size) - wrong syntax!
    if(!ret)
        return $1 0;
        
    // Copy the input to return buffer
    zero(ret, size + 1);
    copy(ret, buffer, size);

    return ret;
}

void prompt(){

    printf("@> ");
    fflush(stdout);

    return;

}

void mainloop(bool *cptr){

    int8* cmd;

    prompt();
    cmd = readline();
    if(cmd){
        if(!strcmp($c cmd, "exit"))
            *cptr = false;
        else
            printf("......\n");

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