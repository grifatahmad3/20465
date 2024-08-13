#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "essentials.h"
#include "preasm.h"

int main(int argc, char *argv[]){

    ERR *err;
    Macro *macros;
    int i = 1;
    char *file = NULL;

    err = NULL;
    macros = NULL;

    while(i < argc){
        printf(PREASSM_START);
        /*start preassm*/
        file = addExtToFilename(EXT_ORIGIN, argv[i], strlen(EXT_ORIGIN));
        printf("\n%s\n\n", file);
        if(startPreAsm(argv[i], &macros, &err) == false){
            printERR(&err);
            return -1;
            }
        if(macros!=NULL){
            printMacros(&macros);
        }
        printf(PREASSM_END);
        i++;
        if (file!=NULL)
            free(file);
    }
    if(macros != NULL){
        freeMacros(&macros);
    }
    if(err!=NULL)
        freeERR(&err);

    return 0;
}