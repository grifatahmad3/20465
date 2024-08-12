
#include "preasm.h"
#include "essentials.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Bool startPreAsm(char* filename, ERR **err) {

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


    Macro *macros;
    char *filer, *filew; /*filer = file to read, filew = file to write*/
    char line[MAX_LINE+1], str[MAX_LINE+1], macroName[MAX_LINE+1];
    FILE *fpr, *fpw; /*fpr = file pointer to read, fpw = file pointer to write*/
    Bool inMacro;

    macros = NULL;
    inMacro = false;
    filer = addExtToFilename(EXT_ORIGIN, filename, strlen(EXT_ORIGIN));
    filew = addExtToFilename(EXT_PREASM, filename, strlen(EXT_PREASM));
    fpr = fopen(filer, "r");
    fpw = fopen(filew, "w");

    if (fpr == NULL || fpw == NULL) {
        addERR(err, FILE_ERROR);
        return false;
    }

    while (fgets(line, MAX_LINE, fpr) != NULL /*step 1*/) {

        sscanf(line, "%s", str);
        /*step 6:*/
        if(inMacro == true && strcmp(str, "endmacr")!=0) {
            addMacroDefinition(findMacro(&macros, macroName), line);
            continue;
        }

        /*step 7 and 8: */
        if(!strcmp(str, "endmacr")) {
            inMacro=false;
            continue;
        }

        /*step 2:*/
        if(findMacro(&macros, str)!=NULL) {
            fputs(findMacro(&macros, str)->definition, fpw);
            continue;
        }

        /*step 3:*/
        if(!strcmp(str, "macr")) {
            /*step 4*/
            inMacro = true;
            /*step 5*/
            if(sscanf(line, "%s %s", str, macroName)==2) {
                if(addMacro(&macros, macroName, "") == false) {
                    addERR(err, MACRO_ADD_FAIL);
                    break;
                }
            }
            else {
                addERR(err, WORD_FAILED);
                break;
            }
            continue;
        }
        fputs(line, fpw);
    }

    printMacros(&macros);
    freeMacros(&macros);

    fclose(fpw);
    fclose(fpr);
    free(filew);
    free(filer);


    return true;
}