#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "essentials.h"
#include "preasm.h"

int main(int argc, char *argv[]){
   
    int i = 1;
    char *file = NULL;
    

    while(i < argc){
        printf(PREASSM_START);
        /*start preassm*/
        file = addExtToFilename(".asm", argv[i], 4);
        printf("\n%s\n\n", file);
        startPreAsm();
        printf(PREASSM_END);
        i++;
    }
    if (file!=NULL) 
        free(file);
    return 0;
}