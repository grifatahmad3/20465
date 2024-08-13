#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "essentials.h"
#include "preasm.h"

int main(int argc, char *argv[]){

    ERR *err;
    Macro *macros;
    int i = 1;


    macros = NULL;


    while(i < argc){
        err = NULL; /*new err list for each file*/

        printf("\nFile: %s.as\n\n", argv[i]);
        printf(PREASSM_START);
        if(startPreAsm(argv[i], &macros, &err) == false){
            printERR(&err);
            freeERR(&err);
            i++;
            continue;
            }
        if(err!=NULL){ /*should be removed soon because it's unnecessary*/
            printERR(&err);
            freeERR(&err);
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
        i++;
        if(err!=NULL)
            freeERR(&err);
    }

    /* before exiting*/
    if(macros != NULL){
        freeMacros(&macros);
    }

    return 0;
}