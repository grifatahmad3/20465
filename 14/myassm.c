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

        /*start preassm*/
        file = addExtToFilename(EXT_ORIGIN, argv[i], strlen(EXT_ORIGIN));
        if(file == NULL){
            printf(MALLOC_ERROR);
            i++;
            continue;
        }
        printf("\nFile: %s\n\n", file);
        printf(PREASSM_START);
        if(startPreAsm(argv[i], &macros, &err) == false){
            printERR(&err);
            free(file);
            i++;
            continue;
            }
        if(err!=NULL){
            printERR(&err);
            free(file);
            i++;
            continue;
        }
        printf(PREASSM_END);
        /*end preassm*/


        /*start first pass*/
        printf(FIRSTPASS_START);
        printf(FIRSTPASS_END);
        /*end first pass*/


        /*start second pass*/
        printf(SECONDPASS_START);
        printf(SECONDPASS_END);
        /*end second pass*/

        printf("\n\n");
        free(file);
        i++;
    }

    /* before exiting*/
    if(macros != NULL){
        freeMacros(&macros);
    }
    if(err!=NULL)
        freeERR(&err);
    return 0;
}