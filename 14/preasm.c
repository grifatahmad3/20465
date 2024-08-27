/* Implementaions of preasm.h */

#include "preasm.h"
#include "essentials.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

Bool startPreAsm(char* filename, Macro **macros, ERR **err) {

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
    
    char *filer, *filew; /*filer = file to read, filew = file to write*/
    char line[MAX_LINE+1], str[MAX_LINE+1], macroName[MAX_LINE+1] = "\0";
    FILE *fpr, *fpw; /*fpr = file pointer to read, fpw = file pointer to write*/
    Bool inMacro;
    int line_num = 0;
    char *token;

    inMacro = false;
    filer = addExtToFilename(EXT_ORIGIN, filename, strlen(EXT_ORIGIN));
    if (filer == NULL) {
        addERR(err, MALLOC_ERROR, 0);
        return false;
    }
    filew = addExtToFilename(EXT_PREASM, filename, strlen(EXT_PREASM));
    if (filew == NULL) {
        addERR(err, MALLOC_ERROR, 0);
        free(filer);
        return false;
    }

    fpr = fopen(filer, "r");
    if (fpr == NULL) {
        addERR(err, FILE_ERROR, 0);
        free(filer);
        free(filew);
        return false;
    }

    fpw = fopen(filew, "w");
    if (fpw == NULL) {
        addERR(err, FILE_ERROR, 0);
        free(filer);
        free(filew);
        fclose(fpr);
        return false;
    }

    while (fgets(line, MAX_LINE+1, fpr) != NULL /*step 1*/) {

        line_num++;
        if(strlen(line)==MAX_LINE && *(line+(MAX_LINE-1))!='\n'){
            addERR(err, LINE_TOO_LONG, line_num);
            break;
        }

        strcpy(str, line);
        token = strtok(str, " \t\n");
        /*if(sscanf(line, "%s", str) < 1){
            continue;
        }*/
        if(token == NULL){
            continue;
        }
        /*if(strcmp(token, "\n")==0){
            continue;
        }*/

        /*step 6:*/
        if(inMacro == true && strcmp(token /*str*/, "endmacr")!=0) {
            addMacroDefinition(findMacro(macros, macroName), line);
            continue;
        }

        /*step 7 and 8: */
        if(strcmp(token /*str*/, "endmacr") == 0) {
            token = strtok(NULL, " \t\n");
            if(token!=NULL && strcmp(token, "\n")!=0){
                addERR(err, TOO_MUCH_ARGUMENTS, line_num);
                break;
            }
            inMacro=false;
            continue;
        }

        /*step 2:*/
        if(findMacro(macros, token /*str*/)!=NULL) {
            fputs(findMacro(macros, token /*str*/)->definition, fpw);
            continue;
        }

        /*step 3:*/
        if(strcmp(token /*str*/, "macr") == 0) {
            /*step 4*/
            inMacro = true;
            /*step 5*/
            token = strtok(NULL, " \t\n");
            if(token != NULL && strcmp(token, "\n")!=0 /*sscanf(line, "%s %s", str, macroName)==2*/) {
                strcpy(macroName, token);
                if(findMacro(macros, macroName)==NULL && findOP(macroName)==NULL && findReg(macroName)==-1){
                    if(addMacro(macros, macroName, "") == false) {
                        addERR(err, MACRO_ADD_FAIL, line_num);
                        break;
                    }
                }
                else{
                    addERR(err, ILLEGAL_MACRO_NAME, line_num);
                    break;
                }
            }
            else {
                addERR(err, WORD_FAILED, line_num);
                break;
            }
            token = strtok(NULL, " \t\n");
            if(token != NULL && strcmp(token, "\n")!=0){
                addERR(err, TOO_MUCH_ARGUMENTS, line_num);
                break;
            }
            continue;
        }
        fputs(line, fpw);
    }

    fclose(fpw);
    fclose(fpr);
    free(filew);
    free(filer);

    if(*err!=NULL){
        return false;
    }
    return true;
}