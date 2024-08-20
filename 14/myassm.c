#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "essentials.h"
#include "preasm.h"
#include "firstpass.h"


int main(int argc, char *argv[]){

    ERR *err;
    Macro *macros;
    Symbol *symbols;
    int i = 1;
    int IC=100, DC=100;


    macros = NULL;
    symbols = NULL;

    while(i < argc){
        err = NULL; /*new err list for each file*/

        printf("\nFile: %s.as\n\n", argv[i]);
        printf(PREASSM_START);
        if(startPreAsm(argv[i], &macros, &err) == false){
            if(err!=NULL){
                printERR(&err);
                freeERR(&err);
            }
            i++;
            continue;
            }
        printf(PREASSM_END);
        /*end preassm*/


        /*start first pass*/
        printf(FIRSTPASS_START);
        if(startFirstPass(argv[i], &macros, &err, &symbols, &IC, &DC) == false){
            if(err!=NULL){
                printERR(&err);
                freeERR(&err);
            }
            i++;
            continue;
        }
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