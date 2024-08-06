#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "essentials.h"

int main(int argc, char *argv[]){
   
    int i = 1;
    char *file;
    Macro *new_macro = (Macro*) malloc(sizeof(Macro));
    strcpy(new_macro->name, "Macro1");
    strcpy(new_macro->definition, "Line1\nLine2\nLine3");
    new_macro->next=NULL;
    

    while(i < argc){
        printf(PREASSM_START);
        /*start preassm*/
        file = addExtToFilename(".asm", argv[i], 4);
        printf("\n%s\n\n", file);
        printMacros(new_macro);
        printf(PREASSM_END);
        i++;
    }

    
    free(new_macro);
    return 0;
}