/* Implementaions of firstpass.h */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "firstpass.h"
#include "essentials.h"


    /*  The Algorithm
    *
    *   1- set IC=100, DC=1;
    *   2- read next line. if EOF then jump to 14. if (IC+DC) > (RAM_SIZE+1) then err. if empty line or comment then skip.
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

    /*  These start like to fit the implementation of the algorithm explained above.
     * Specifically, to set the address of an encountered symbol that hasn't been defined yet to 0*/
    (*IC) = 100; /*step 1*/
    (*DC) = 1;
    
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

        
        if((*IC+*DC) > (RAM_SIZE+1)){
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
            token = strtok(NULL, " \t\n");
            if(token==NULL || *token == ';'){
                addERR(err, SYMBOL_EMPTY, line_num);
                continue;
            }
            /*if the next word is .entry or .extern then ignore the symbol*/
            if(strcmp(token, ENTRY) == 0 || strcmp(token, EXTERN)==0){
                inSymbol = false;
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
                    temp_symbol->address = *DC;
                    temp_symbol->sfor = forData;
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
                token = strtok(NULL, " \t\n");
                if(token==NULL){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                if(parseLineData(token, data_array, &array_size) == false){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                for(index=0; index<array_size; index++){
                    if(addMachineCode(data, 0+data_array[index], *DC, index==0?temp_str:NULL) == false){
                        addERR(err, MALLOC_ERROR, line_num);
                        continue;
                    }
                    (*DC)++;
                }
                continue;
            }

            else if(strcmp(token, STRING) == 0){
                token = strtok(NULL, " \t\n");
                if(token==NULL){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                if(parseLineString(token, data_array, &array_size) == false){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                for(index=0; index<array_size-1; index++){
                    if(addMachineCode(data, 0+(unsigned char)data_array[index], *DC, index==0?temp_str:NULL) == false){
                        addERR(err, MALLOC_ERROR, line_num);
                        continue;
                    }
                    (*DC)++;
                }
                if(addMachineCode(data, 0, *DC, NULL) == false){ /*adding the last '\0'*/
                        addERR(err, MALLOC_ERROR, line_num);
                        continue;
                    }
                (*DC)++;
                continue;
            }
        }


        /* step 8 */
        if(strcmp(token, ENTRY)==0 || strcmp(token, EXTERN) == 0){
            if(strcmp(token, EXTERN) == 0){
                token = strtok(NULL, " \t\n");
                if(token == NULL){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                if(isLegalSymbolName(token) == false){
                    addERR(err, ILLEGAL_SYMBOL_NAME, line_num);
                    continue;
                }
                if((temp_symbol= findSymbol(symbols, token)) == NULL){
                    if(addSymbol(symbols, token,0+E_FIELD, forNone, ext) == false){
                        addERR(err, MALLOC_ERROR, line_num);
                        continue;
                    }
                }
                else{
                    temp_symbol->type=ext;
                    temp_symbol->address=0+E_FIELD;
                }

                if((token = strtok(NULL, " \t\n"))!=NULL){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
            }

            else if(strcmp(token, ENTRY)==0){
                token = strtok(NULL, " \t\n");
                if(token == NULL){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
                if(isLegalSymbolName(token) == false){
                    addERR(err, ILLEGAL_SYMBOL_NAME, line_num);
                    continue;
                }
                /*ERROR HERE*/
                if((temp_symbol= findSymbol(symbols, token)) != NULL && temp_symbol->type==none){
                    temp_symbol->type = ent;
                }
                if(temp_symbol != NULL && /*(temp_symbol->address == 0 || ) */temp_symbol->type==ext){
                    addERR(err, ILLEGAL_SYMBOL_NAME, line_num);
                    continue;
                }
                if(temp_symbol == NULL){
                    if(addSymbol(symbols, token, 0, forNone, ent) == false){
                        addERR(err, MALLOC_ERROR, line_num);
                        continue;
                    }
                }
                if((token = strtok(NULL, " \t\n"))!=NULL){
                    addERR(err, ILLEGAL_FORMAT, line_num);
                    continue;
                }
            }
            continue;
        }

        /*step 10*/
        if(inSymbol==true){ /*this means we are in a line with a label and an instruction line, such as:- MAIN: add r1,r2*/
            if((temp_symbol= findSymbol(symbols, temp_str)) != NULL && temp_symbol->address!=0){
                addERR(err, ILLEGAL_SYMBOL_NAME, line_num);
                continue;
            }
            if(temp_symbol != NULL && temp_symbol->address==0){
                temp_symbol->sfor = forInst;
                temp_symbol->address = *IC;
                /*add the line to MachineCode**inst in the coming step, with label=symbol_name if (inSymbol==true) to the first line*/
            }
            if(temp_symbol==NULL){
                if(addSymbol(symbols, temp_str, *IC, forInst, none)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    /*add the line to MachineCode**inst in the coming step, with label=symbol_name if (inSymbol==true) to the first line*/
                    continue;
                }
            }
        }

        /*step 11*/
        if(findOP(token)!=NULL){
            if(proccessInstLine(err, inst, IC, token, inSymbol, inSymbol==false?NULL:temp_str, symbols, line_num)==false){
                /*errors are handled inside the function, so no need to add here*/
                continue;
            }
        }
        else{
            addERR(err, ILLEGAL_FORMAT, line_num);
            continue; /*unnecessary, exists to stress the idea that we continue to find all errors*/
        }
        
        
    }

    /*step 14*/
    fclose(fpr);
    free(filer);
    if(*err!=NULL){
        return false;
    }
    return true;
}


Bool isNumber(char *str) {
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

Bool parseLineData(char *line, int *array, size_t *size) {
    size_t index = 0;
    char temp_line[MAX_LINE] = "";
    char *ptr = temp_line;
    char buffer[WORD_SIZE];
    Bool expect_number = true;

    while(line != NULL){
        strcat(temp_line, line);
        line = strtok(NULL, "\n");
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

            if (*buffer == '\0' || !isNumber(buffer)){
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

Bool parseLineString(char *token, int *array, size_t *size){
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

Bool proccessInstLine(ERR **err, MachineCode **inst, int *IC, char *token, Bool inSymbol, char *symbolName, Symbol **symbols, int line_num){
                /*the rest of the steps*/
            /*
            add the line to MachineCode**inst in the coming step, with label=symbol_name if (inSymbol==true) to the first line
    *   12- proccess the line into machine code and calculate how much binary lines are needed (= L).
    *       build the code and add to MachineCode **inst.
    *   13- update IC = IC+L, jump to 2.*/
   /*char temp_line[MAX_LINE] = "\0";*/
   char opr1[MAX_LINE] = "\0"; 
   char opr2[MAX_LINE] = "\0";
   OprType type1;
   OprType type2;
   Symbol *temp_symbol;
   int lateral;
   int code_line1 = 0, code_line2 = 0, code_line3 = 0;
   OP *operation = findOP(token);
   char *str1, *str2;

   if(operation->opr_num==0){ /*it's rts or stop*/
        code_line1 += (BITS11_14(operation->opcode) + A_FIELD);
        token = strtok(NULL, " \t\n");
        if(token != NULL){
            addERR(err, ILLEGAL_FORMAT, line_num);
            return false;
        }
        if(addMachineCode(inst, code_line1, *IC, symbolName) == false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
        }
        (*IC)++;
        return true;
   }


   if(operation->opr_num==1){
        code_line1 += (BITS11_14(operation->opcode) + A_FIELD);
        token = strtok(NULL, " \t\n");
        if(token == NULL){
            addERR(err, ILLEGAL_FORMAT, line_num);
            return false;
        }
        if((type1 = findOprType(token)) == noOp){
            addERR(err, ILLEGAL_FORMAT, line_num);
            return false;
        }

        switch (type1)
        {
        case imm:{
            lateral = atoi(token+1);
            if(lateral>MAX_NUMBER || lateral<MIN_NUMBER){
                addERR(err, NUM_OUT_OF_BOUND, line_num);
                return false;
            }
            code_line1 += (BITS3_6(IMM_ACCESS));
            code_line2 = BITS3_14(lateral)+A_FIELD;
            break;
        }
        case dir:{
            if(inSymbol == true && strcmp(token, symbolName)==0){
                /*addERR(err, ILLEGAL_FORMAT, line_num);
                return false;*/
                printf("WARNING: At line: %d, operand name is the same as a label name!\n", line_num);
            }
            code_line1 += (BITS3_6(DIR_ACCESS));
            if((temp_symbol=findSymbol(symbols, token))!=NULL){
                code_line2 = BITS3_14((temp_symbol->address));
                if(temp_symbol->type!=ext){
                    code_line2 |= (R_FIELD);
                }
                /*
                if(temp_symbol->type == ext){
                    code_line2 += (E_FIELD);
                }*/
            }
            if(temp_symbol==NULL){
                if(addSymbol(symbols, token, 0, forNone, none)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                code_line2 = 0;
            }
            break;
        }

        case regDir:{
            code_line1 += (BITS3_6(DIR_REG_ACCESS));
            code_line2 += (BITS3_5(findReg(token)) + A_FIELD);
            break;
        }
        case regIndir:{
            code_line1 += (BITS3_6(IND_REG_ACCESS));
            code_line2 += (BITS3_5(findReg(token+1)) + A_FIELD);
            break;
        }
        default:
            break;
        }

        if((temp_symbol=findSymbol(symbols, token))!=NULL){
            str1 = temp_symbol->name;
        }
        else{
            str1 = NULL;
        }

        if(strcmp(operation->name, "prn")==0){
            if(addMachineCode(inst, code_line1, *IC, inSymbol==true?symbolName:NULL)==false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
            }
            if(inSymbol==true){
                temp_symbol = findSymbol(symbols, symbolName);
                temp_symbol->address = *IC;
                temp_symbol->sfor = forInst;
            }
            (*IC)++;
            if(addMachineCode(inst, code_line2, *IC, str1) == false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
            }
            (*IC)++;
        }
        
        else if(strcmp(operation->name, "jsr")==0 ||
           strcmp(operation->name, "bne")==0 ||
           strcmp(operation->name, "jmp")==0){
            if(type1==dir || type1==regIndir){
                if(addMachineCode(inst, code_line1, *IC, NULL)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                if(inSymbol==true){
                    temp_symbol = findSymbol(symbols, symbolName);
                    temp_symbol->address = *IC;
                    temp_symbol->sfor = forInst;
                 }
                (*IC)++;
                if(addMachineCode(inst, code_line2, *IC, str1) == false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
                }
                (*IC)++;
            }
            else{
                addERR(err, ILLEGAL_FORMAT, line_num);
                return false;
            }
        }
        
        else {
            if(type1 == imm){
                addERR(err, ILLEGAL_FORMAT, line_num);
                return false;
            }
            if(addMachineCode(inst, code_line1, *IC, NULL)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
            if(inSymbol==true){
                temp_symbol = findSymbol(symbols, symbolName);
                temp_symbol->address = *IC;
                temp_symbol->sfor = forInst;
            }
            (*IC)++;
            if(addMachineCode(inst, code_line2, *IC, str1) == false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
            }
            (*IC)++;
        }
        return true;
   }


   if(operation->opr_num==2){
    code_line1 += (BITS11_14(operation->opcode) + A_FIELD);
        token = strtok(NULL, "\n");
        if(token == NULL){
            addERR(err, ILLEGAL_FORMAT, line_num);
            return false;
        }
        if(parseTwoOperands(token, opr1, opr2) == false){
            addERR(err, ILLEGAL_FORMAT, line_num);
            return false;
        }
        if((type1=findOprType(opr1))==noOp){
            addERR(err, ILLEGAL_FORMAT, line_num);
            return false;
        }

       if((type2=findOprType(opr2))==noOp){
           addERR(err, ILLEGAL_FORMAT, line_num);
           return false;
       }

        switch (type1)
        {
        case imm:{
            lateral = atoi(opr1+1);
            if(lateral>MAX_NUMBER || lateral<MIN_NUMBER){
                addERR(err, NUM_OUT_OF_BOUND, line_num);
                return false;
            }
            code_line1 += (BITS7_10(IMM_ACCESS));
            code_line2 = BITS3_14(lateral)+A_FIELD;
            break;
        }
        case dir:{
            if(inSymbol==true && strcmp(opr1, symbolName)==0){
                /*addERR(err, ILLEGAL_FORMAT, line_num);
                return false;*/
                printf("WARNING: At line: %d, operand name is the same as a label name!\n", line_num);
            }
            code_line1 += (BITS7_10(DIR_ACCESS));
            if((temp_symbol=findSymbol(symbols, opr1))!=NULL){
                if(temp_symbol->address != 0 && temp_symbol->type!=ext){
                    code_line2 = BITS3_14((temp_symbol->address));
                    code_line2 += (R_FIELD);
                }
                else {
                    code_line2 = temp_symbol->address;
                }
                if(temp_symbol->sfor==forNone){
                    temp_symbol->sfor=forData;
                }
                /*code_line2 = BITS3_14((temp_symbol->address));
                if(temp_symbol->type==ent){
                    code_line2 += (R_FIELD);
                }
                if(temp_symbol->type == ext){
                    code_line2 += (E_FIELD);
                }
                */
            }
            if(temp_symbol==NULL){
                if(addSymbol(symbols, opr1, 0, forData, none)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                code_line2 = 0;
            }
            break;
        }

        case regDir:{
            code_line1 += (BITS7_10(DIR_REG_ACCESS));
            code_line2 += (BITS6_8(findReg(opr1)) + A_FIELD);
            break;
        }
        case regIndir:{
            code_line1 += (BITS7_10(IND_REG_ACCESS));
            code_line2 += (BITS6_8(findReg(opr1+1)) + A_FIELD);
            break;
        }
        default:
            break;
        }

        switch (type2)
        {
        case imm:{
            lateral = atoi(opr2+1);
            if(lateral>MAX_NUMBER || lateral<MIN_NUMBER){
                addERR(err, NUM_OUT_OF_BOUND, line_num);
                return false;
            }
            code_line1 += (BITS3_6(IMM_ACCESS));
            code_line3 = BITS3_14(lateral)+A_FIELD;
            break;
        }
        case dir:{
            if(inSymbol==true && strcmp(opr2, symbolName)==0){
                /*addERR(err, ILLEGAL_FORMAT, line_num);
                return false;*/
                printf("WARNING: At line: %d, operand name is the same as a label name!\n", line_num);
            }
            code_line1 += (BITS3_6(DIR_ACCESS));
            if((temp_symbol=findSymbol(symbols, opr2))!=NULL){
                
                if(temp_symbol->address != 0 && temp_symbol->type!=ext){
                    code_line3 = BITS3_14((temp_symbol->address));
                    code_line3 += (R_FIELD);
                }
                else {
                    code_line3 = temp_symbol->address;
                }
                /*
                if(temp_symbol->address!=-1){
                    code_line3 = BITS3_14((temp_symbol->address));
                }
                if(temp_symbol->type==ent){
                    code_line3 += (R_FIELD);
                }
                if(temp_symbol->type == ext){
                    code_line3 += (E_FIELD);
                }*/
            }
            if(temp_symbol==NULL){
                if(addSymbol(symbols, opr2, 0, forData, none)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                code_line3 = 0;
            }
            break;
        }

        case regDir:{
            code_line1 += (BITS3_6(DIR_REG_ACCESS));
            code_line3 += (BITS3_5(findReg(opr2)) + A_FIELD);
            break;
        }
        case regIndir:{
            code_line1 += (BITS3_6(IND_REG_ACCESS));
            code_line3 += (BITS3_5(findReg(opr2+1)) + A_FIELD);
            break;
        }
        default:
            break;
        }


       if((temp_symbol = findSymbol(symbols, opr1)) != NULL){
           str1 = temp_symbol->name;
       }
       else{
           str1 = NULL;
       }

       if((temp_symbol = findSymbol(symbols, opr2)) != NULL){
           str2 = temp_symbol->name;
       }
       else{
           str2 = NULL;
       }

        if(strcmp(operation->name, "lea")==0){
            if(type1!=dir || type2==imm){
                addERR(err, ILLEGAL_FORMAT, line_num);
                return false;
            }
            if(addMachineCode(inst, code_line1, *IC, inSymbol==true?symbolName:NULL)==false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
            }
            if(inSymbol==true){
                temp_symbol = findSymbol(symbols, symbolName);
                temp_symbol->address = *IC;
                temp_symbol->sfor = forInst;
            }
            (*IC)++;
            if(addMachineCode(inst, code_line2, *IC, str1)==false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
            }
            (*IC)++;
            if(addMachineCode(inst, code_line3, *IC, str2)==false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
            }
            (*IC)++;
        }
        
        else if(strcmp(operation->name, "cmp")==0){
            if(addMachineCode(inst, code_line1, *IC, inSymbol==true?symbolName:NULL)==false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
            }
            if(inSymbol==true){
                temp_symbol = findSymbol(symbols, symbolName);
                temp_symbol->address = *IC;
                temp_symbol->sfor = forInst;
            }
            (*IC)++;
            if((type1==regDir || type1==regIndir) && (type2==regDir || type2==regIndir)){
                code_line2 |= code_line3;
                if(addMachineCode(inst, code_line2, *IC, NULL)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                (*IC)++;
            }
            else{
                if(addMachineCode(inst, code_line2, *IC, str1)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                (*IC)++;
                if(addMachineCode(inst, code_line3, *IC, str2)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                (*IC)++;
            }
        }

        else{
            if(type2==imm){
                addERR(err, ILLEGAL_FORMAT, line_num);
                return false;
            }
            if(addMachineCode(inst, code_line1, *IC, inSymbol==true?symbolName:NULL)==false){
                addERR(err, MALLOC_ERROR, line_num);
                return false;
            }
            if(inSymbol==true){
                temp_symbol = findSymbol(symbols, symbolName);
                temp_symbol->address = *IC;
                temp_symbol->sfor = forInst;
            }
            (*IC)++;
            if((type1==regDir || type1==regIndir) && (type2==regDir || type2==regIndir)){
                code_line2 |= code_line3;
                if(addMachineCode(inst, code_line2, *IC, NULL)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                (*IC)++;
            }
            else{
                if(addMachineCode(inst, code_line2, *IC, str1)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                (*IC)++;
                if(addMachineCode(inst, code_line3, *IC, str2)==false){
                    addERR(err, MALLOC_ERROR, line_num);
                    return false;
                }
                (*IC)++;
            }
        }
        
    return true;
   }

   return false;
}

Bool parseTwoOperands(char *token, char *word1, char *word2) {
    char line_copy[MAX_LINE+1] = "";
    char *ptr = line_copy;
    int i = 0;

    if(token==NULL){
        return false;
    }

    while(token!=NULL){
        strcat(line_copy, token);
        token = strtok(NULL, "\n");
    }


    while (isspace((unsigned char)*ptr)) {
        ptr++;
    }


    if (*ptr == ',' || *ptr == '\0') {
        return false;
    }

    while (*ptr != '\0' && *ptr != ',' && !isspace((unsigned char)*ptr) && i < MAX_LINE) {
        word1[i++] = *ptr++;
    }
    word1[i] = '\0';


    while (isspace((unsigned char)*ptr)) {
        ptr++;
    }

 
    if (*ptr != ',') {
        return false;
    }
    ptr++;

    while (isspace((unsigned char)*ptr)) {
        ptr++;
    }

    if (*ptr == ',') {
        return false; 
    }


    while (isspace((unsigned char)*ptr)) {
        ptr++;
    }


    if (*ptr == '\0') {
        return false; 
    }

    i = 0;
    while (*ptr != '\0' && *ptr != ',' && !isspace((unsigned char)*ptr) && i < MAX_LINE) {
        word2[i++] = *ptr++;
    }
    word2[i] = '\0';

    while (isspace((unsigned char)*ptr)) {
        ptr++;
    }

    if (*ptr != '\0') {
        return false;
    }

    return true;
}