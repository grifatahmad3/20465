#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "essentials.h"
#include "preasm.h"

int main(int argc, char *argv[]){
   
    int i = 1;
    char *file;

    while(i < argc){
        printf(PREASSM_START);
        /*start preassm*/
        file = addExtToFilename(EXT_ORIGIN, argv[i], strlen(EXT_ORIGIN));
        printf("\n%s\n\n", file);
        if(startPreAsm(file) == false){
            printf(FILE_ERROR);
            return -1;
            }
        printf(PREASSM_END);
        i++;
    }
    if (file!=NULL) 
        free(file);
    return 0;
}