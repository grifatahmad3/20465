
#include "preasm.h"
#include "essentials.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool startPreAsm(char* filename){

    /* 1- Read next line, if EOF jump to 9
       2- is first word a defined macro? if yes, replace the name with the definition, and go back to 1. else move on.
       3- is first word "macr"? if no go to 6. if yes go on.
       4- raise flag "there is a macro"
       5- copy the next word to the macro name
       6- read next line. if EOF, then jump to 9. if "there is macro" and not yet "endmacr", copy to the content of the macr and don't write to the new file. else (not macro) go back to 1.
       7- is "endmacr"? if yes then don't write it to the new file. else jump back to 6.
       8- turn off "there is macro" flag, jump back to 1 (finished saving macr).
       9- eof
    */


    char *filer, *filew;
    char str[MAX_LENGTH];
    FILE *fpr, *fpw;

    filer = addExtToFilename(EXT_ORIGIN, filename, strlen(EXT_ORIGIN));
    filew = addExtToFilename(EXT_PREASM, filename, strlen(EXT_PREASM));
    fpr = fopen(filer, "r");
    fpw = fopen(filew, "w");

    if(fpr==NULL || fpw==NULL)
        return false;

    while (fgets(str, MAX_LENGTH, fpr) != NULL){
        fputs(str, fpw);
    }


    fclose(fpw);
    fclose(fpr);
    printf("\n\n");
    return true;
}