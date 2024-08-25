/* Implementaions of firstpass.h */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "firstpass.h"
#include "essentials.h"


    /*  The Algorithm
    *
    *   1- set IC=0, DC=0;
    *   2- read next line. if EOF then jump to 14. if (IC+DC) > (RAM_SIZE-STARTING_ADDRESS) then err. if empty line or comment then skip.
    *   3- is the first field(token) a symbol? if yes and second token is .entry or .extern jump to 8, or if no jump to step 5
    *   4- set flag isSymbol=true;
    *   5- is this data command (.data or .string)?, if no jump to step 8
    *   6-      if isSymbol==true: - if symbol exists with address!=0, add err.
    *                              - if symbol exists with type=ent, update it with sfor=data and address=DC.
    *                              - if symbol doesn't exist, add to symbols with sfor=data and address=DC and type=none. 
    *                         
    *   7- recognize the type of data (.data or .string?), add to MachineCode **data with address of DC, 
    *       update DC accordingly, and enter with the label symbol for the first line. jump to 2
    *   8- is this .extern or .entry? if no jump to step 11
    *   9- is this .extern? if yes:
    *                       - if it doesn't exist, add to Symbols with type=ext, sfor=forNone, address=(0+E_FIELD). jump to step 2
    *                       - if it does exist then err.
    *      is this .entry? if yes: 
    *                       - if it does exist with address!=0, update type=ent.
    *                       - if it does exist with address==0, add err. //because it could be either entry but not defined or extern
    *                       - it doesn't exist, add to Symbols with type=ent, sfor=forNone(will be updated when it's found), address=0(unknown).
    *                       
    *                      if other tokens exist then add error. jump to step 2
    * 
    *   10- if isSymbol==true: - if it does exist with address!=0, add err.
    *                          - if it does exist with address==0, update it with sfor=forInst, address=IC, and add the line
    *                                to MachineCode **inst with the first line having label=symbol
    *                          - if it doesn't exist, add to Symbols with sfor=forInst, type=none, address=IC 
    *                               and add the line to MachineCode **inst with the first line having label=symbol
    *   11- search if the first token (maybe second symbol) is an operation. if it's not then err.
    *   12- proccess the line into machine code and calculate how much binary lines are needed (= L).
    *       build the code and add to MachineCode **inst.
    *   13- update IC = IC+L, jump to 2.
    *   14- finished reading the file, if err!=NULL don't go to 2nd stage and print all errs.
    * 
    * 
    *   if no errors detected: update address = address+STARTING_ADDRESS in (MachineCode **inst && Symbol **symbols with sfor=forInst(),
    *                          update IC = IC+STARTING_ADDRESS
    *                          update DC = DC+IC in (MachineCode **data && **symbols with sfor=forData).
    * 
    *   In 2nd pass, go over all MachineCode **inst and update address of instances with label from Symbol **symbols with sfor=forInst,
    *                go over all MachineCode **data and update address of instances with label from Symbol **symbols with sfor=forData.
    *   If all is good, make all output files with the necessarry format.
    * */

Bool startFirstPass(char* filename, Macro **macros, ERR **err, Symbol **symbols, int *IC, int *DC, MachineCode **inst, MachineCode **data){

    char *filer; /*filer = file to read*/
    char line[MAX_LINE+1], line_copy[MAX_LINE+1], temp_str[MAX_LINE+1];
    FILE *fpr; /*fpr = file pointer to read, fpw = file pointer to write*/
    Bool inSymbol;
    int line_num = 0;
    char *token;
    Symbol *temp_symbol;
    int data_array[MAX_LINE];
    size_t array_size;
    int index = 0;

    (*IC) = 0; /*step 1*/
    (*DC) = 0;
    
    filer = addExtToFilename(EXT_PREASM, filename, strlen(EXT_PREASM));
    if (filer == NULL) {
        addERR(err, MALLOC_ERROR, 0);
        return false;
    }

    fpr = fopen(filer, "r");
    if (fpr == NULL) {
        addERR(err, FILE_ERROR, 0);
        free(filer);
        return false;
    }

    /*step 2*/
    while(fgets(line, MAX_LINE+1, fpr) != NULL){

        line_num++;
        if(strlen(line)==MAX_LINE && *(line+(MAX_LINE-1))!='\n'){
            addERR(err, LINE_TOO_LONG, line_num);
            break;
        }

        inSymbol = false;
        strcpy(temp_str, "\0");

        
        if((*IC+*DC) > (RAM_SIZE-STARTING_ADDRESS)){ 
            addERR(err, RAM_EMPTY, line_num);
            break;
        }

        strcpy(line_copy, line);
        token = strtok(line_copy, " \t\n");
        if(token==NULL || *token == ';'){
            continue;
        }
        
        /*step 3*/
        if(*(token+strlen(token)-1)==':'){
            *(token+strlen(token)-1)='\0';
            if(isLegalSymbolName(token)){
                /*step 4*/
                inSymbol = true;
                strcpy(temp_str, token);
            }
            else{
                addERR(err, ILLEGAL_SYMBOL_NAME, line_num);
                continue;
            }
        }

        /*step 5*/
        if(inSymbol==true){ /*inside symbol, so we need the next word in the line*/
            token = strtok(line_copy, " \t\n");
            if(token==NULL || *token == ';'){
                addERR(err, SYMBOL_EMPTY, line_num);
                continue;
            }
        }
        
        if(strcmp(token, DATA)==0 || strcmp(token, STRING) == 0){
            /*step 6*/
            if(inSymbol == true){
                if((temp_symbol= findSymbol(symbols, temp_str)) != NULL){
                    /*- if symbol exists with address!=0, add err.*/
                    if(temp_symbol->address != 0){
                        addERR(err, SYMBOL_EXISTS, line_num);
                        continue;
                    }
                    /*- if symbol exists with type=ent, update it with sfor=data and address=DC.*/
                    if(temp_symbol->type==ent){
                        temp_symbol->address = *DC;
                        temp_symbol->sfor = forData;
                    }
                }
                else{ /*- if symbol doesn't exist, add to symbols with sfor=data and address=DC and type=none. */
                    if(addSymbol(symbols, temp_str, *DC, forData, none)==false){
                        addERR(err, MALLOC_ERROR, line_num);
                        continue;
                    }
                }
            }
            /*  TODO:
            step 7 */
            if(strcmp(token, DATA)==0){
                token = strtok(line_copy, " \t\n");
                if(token==NULL){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                if(parse_line_data(token, data_array, &array_size) == false){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                for(index=0; index<array_size; index++){
                    if(addMachineCode(data, 0+data_array[index], *DC, index==0?temp_str:"") == false){
                        addERR(err, MALLOC_ERROR, line_num);
                        continue;
                    }
                    (*DC)++;
                }
                continue;
            }

            if(strcmp(token, STRING) == 0){
                token = strtok(line_copy, " \t\n");
                if(token==NULL){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                if(parse_line_string(token, data_array, &array_size) == false){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                for(index=0; index<array_size-1; index++){
                    if(addMachineCode(data, 0+(unsigned char)data_array[index], *DC, index==0?temp_str:"") == false){
                        addERR(err, MALLOC_ERROR, line_num);
                        continue;
                    }
                    (*DC)++;
                }
                continue;
            }
        }


        /*  TODO:
        step 8
        8- is this .extern or .entry? if no jump to step 11
    *   9- is this .extern? if yes:
    *                       - if it doesn't exist, add to Symbols with type=ext, sfor=forNone, address=(0+E_FIELD). jump to step 2
    *                       - if it does exist then err.
    *      is this .entry? if yes: 
    *                       - if it does exist with address!=0, update type=ent.
    *                       - if it does exist with address==0, add err. //because it could be either entry but not defined or extern
    *                       - it doesn't exist, add to Symbols with type=ent, sfor=forNone(will be updated when it's found), address=0(unknown).
    *                       
    *                      if other tokens exist then add error. jump to step 2
    * 
        */
        if(strcmp(token, ENTRY)==0 || strcmp(token, EXTERN) == 0){
            continue;
        }
    }
    return true;
}


Bool is_number(char *str) {
    if (*str == '+' || *str == '-') {
        str++;
        }
    if (*str == '\0'){
        return false;
    } 
    while (*str) {
        if (!isdigit(*str)) return false;
        str++;
    }
    return true;
}

Bool parse_line_data(char *token, int *array, size_t *size) {
    size_t index = 0;
    char temp_line[MAX_LINE] = "";
    char *ptr = temp_line;
    char buffer[WORD_SIZE];
    Bool expect_number = true;

    while(token!=NULL){
        strcat(temp_line, token);
        token = strtok(NULL, "\n");
    }

    memset(buffer, 0, sizeof(buffer));

    while (*ptr) {
        while (isspace(*ptr)) {
            ptr++;
        }

        if (*ptr == '\0') {
            if (expect_number) return false;
            break;
        }

        if (expect_number) {
            char *buf_ptr = buffer;
            while (*ptr && !isspace(*ptr) && *ptr != ',') {
                if ((buf_ptr - buffer) < sizeof(buffer) - 1) {
                    *buf_ptr++ = *ptr;
                }
                ptr++;
            }
            *buf_ptr = '\0';

            if (*buffer == '\0' || !is_number(buffer)){
                return false;
            } 

            array[index] = atoi(buffer);
            if (index+1 >= MAX_LINE || array[index] > MAX_DATA_NUM || array[index] < MIN_DATA_NUM){
                return false;
            }
            index++;

            memset(buffer, 0, sizeof(buffer));

            expect_number = false;
        }

        while (isspace(*ptr)) {
            ptr++;
        }

        if (*ptr == ',') {
            ptr++;
            expect_number = true;
        } else if (*ptr != '\0') {
            return false;
        }
    }

    if (expect_number) {
        return false;
    }

    *size = index;
    return true;
}

Bool parse_line_string(char *token, int *array, size_t *size){
    char temp_line[MAX_LINE] = "";
    int i = 1;
    *size = 0;
    if(token == NULL || *token != '\"'){
        return false;
    }
    (*size)++;
    while(token != NULL){
        strcat(temp_line, token);
        token = strtok(NULL, "\n");
    }
    for(i=1; i<MAX_LINE; i++){
        if(temp_line[i] == '\"'){
            if(i<MAX_LINE-2 && temp_line[i+1]){
                return false;
            }
            return true;
        }
        *(array+i-1) = (unsigned char)temp_line[i];
        (*size)++;
    }
    return false;
}