#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "essentials.h"
#include "preasm.h"
#include "firstpass.h"
#include "secondpass.h"


int main(int argc, char *argv[]){

    ERR *err;
    Macro *macros;
    Symbol *symbols;
    MachineCode *inst; /*the instructions body*/
    MachineCode *data; /*the data body*/
    int i = 1;
    int IC=100, DC=1;


    macros = NULL;
    symbols = NULL;
    inst = NULL;
    data = NULL;

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
        if(startFirstPass(argv[i], &macros, &err, &symbols, &IC, &DC, &inst, &data) == false){
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
        if(startSecondPass(argv[i], &err, &symbols, &inst, &data, &IC, &DC)==false){
            if(err!=NULL){
                printERR(&err);
                freeERR(&err);
            }
            i++;
            continue;
        }
        printf(SECONDPASS_END);
        /*end second pass*/

        
        i++;
        if(err!=NULL){
            freeERR(&err);
        }

        /*printSymbols(&symbols);
        printMachineCode(&inst);
        printMachineCode(&data);*/
        
    }

    /* before exiting*/
    if(macros != NULL){
        freeMacros(&macros);
    }
    if(symbols!=NULL){
        freeSymbols(&symbols);
    }
    if(inst!=NULL){
        freeMCs(&inst);
    }
    if(data!=NULL){
        freeMCs(&data);
    }
    return 0;
}