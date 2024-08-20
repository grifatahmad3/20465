/* Implementaions of essentials.h */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "essentials.h"

/*Objects*/

OP operations[OP_NUM] = {
    {"mov", 0, 2},
    {"cmp", 1, 2},
    {"add", 2, 2},
    {"sub", 3, 2},
    {"lea", 4, 2},
    {"clr", 5, 1},
    {"not", 6, 1},
    {"inc", 7, 1},
    {"dec", 8, 1},
    {"jmp", 9, 1},
    {"bne", 10, 1},
    {"red", 11, 1},
    {"prn", 12, 1},
    {"jsr", 13, 1},
    {"rts", 14, 0},
    {"stop", 15, 0}
};

char *registers[REG_NUM] = {
    "r0", "r1", "r2", "r3",
    "r4", "r5", "r6", "r7"
};

/*End Objects*/

/*Functions*/
void printInBinary(unsigned int num){
    int i;
    unsigned mask = 1<<(WORD_SIZE-1);
    for(i=0; i<WORD_SIZE; i++){
        if(num&mask) printf("1");
        else printf("0");
        mask/=2;
    }
}

char* addExtToFilename(char* ext, char* fileName, int num){
    char *temp;
    temp = (char*) malloc(sizeof(char) * MAX_LINE + 1);
    if(temp == NULL){
        return NULL;
    }
    strcpy(temp, fileName);
    strncat(temp, ext, num);
    return temp;
}

int findOP(const char *str){
    int i;
    for(i = 0; i<OP_NUM; i++) {
        if(strcmp(str, operations[i].name) == 0){
            return i;
        }
    }
    return -1;
}

int findReg(const char *str) {
    int i;
    for(i=0; i<REG_NUM; i++) {
        if(strcmp(str, registers[i])==0) {
            return i;
        }
    }
    return -1;
}

Macro* findMacro(Macro **head, char* name){
    Macro *temp;
    temp = *head;
    while (temp != NULL)
    {
        if(!strcmp(temp->name, name)){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Bool addMacro(Macro **head, char* name, char* definition) {
    Macro *new_macro, *temp;
    temp = *head;
    new_macro = (Macro *) malloc(sizeof(Macro));
    if (new_macro == NULL){
        return false;
    }

    new_macro->name = (char*) malloc(sizeof(char)* strlen(name)+1);
    if(new_macro->name == NULL){
        free(new_macro);
        return false;
    }
    strcpy(new_macro->name, name);

    new_macro->definition = (char*) malloc(sizeof(char)* strlen(definition)+1);
    if(new_macro->definition == NULL){
        free(new_macro->name);
        free(new_macro);
        return false;
    }
    strcpy(new_macro->definition, definition);
    new_macro->next = NULL;

    if (temp==NULL) {
        *head = new_macro;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_macro;
    }

    return true;
}

Bool addMacroDefinition(Macro *macro, char* newdef) {
    char *temp;
    if(macro == NULL || newdef == NULL) {
        return false;
    }
    temp = (char*)malloc(sizeof(char)*(strlen(macro->definition)+(strlen(newdef)))+1);
    if(temp == NULL) {
        return false;
    }
    strcpy(temp, macro->definition);
    strcat(temp, newdef);
    free(macro->definition);
    macro->definition = temp;
    return true;
}

void printMacros(Macro **head){
    Macro *temp;
    temp = *head;
    while(temp != NULL){
        printf("Macro:\n");
        printf("%s\n", temp->name);
        printf("%s\n\n", temp->definition);
        temp = temp->next;
    }
}

void freeMacros(Macro **head){
    Macro *curr, *next;
    curr = *head;
    if(curr == NULL)
        return;
    while(curr != NULL){
        next = curr->next;
        free(curr->name);
        free(curr->definition);
        free(curr);
        curr = next;
    }
}

Bool addERR(ERR **head, char* msg, int line_num){
    ERR *temp;
    ERR *new_err;

    temp = *head;
    new_err = (ERR *)malloc(sizeof(ERR));
    if (new_err == NULL) {
        printf("\n!!ERR ALLOCATION ERR!!\n");
        return false;
    }

    new_err->errmsg = (char *)malloc(strlen(msg) + 1);
    if (new_err->errmsg == NULL) {
        free(new_err);
        printf("\n!!ERR ALLOCATION ERR!!\n");
        return false;
    }
    strcpy(new_err->errmsg, msg);
    new_err->line_num = line_num;

    new_err->next = NULL;

    if (temp==NULL) {
        *head = new_err;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_err;
    }
    return true;
}

void printERR(ERR **head){
    ERR *temp;
    temp = *head;
    while(temp != NULL){
        printf("\n");
        if(temp->line_num!=0){
            printf("At line %d: ", temp->line_num);
        }
        printf("%s\n",temp->errmsg);
        temp = temp->next;
    }
}

void freeERR(ERR **head){
    ERR *curr, *next;
    curr = *head;
    if(curr == NULL)
        return;
    while(curr != NULL){
        next = curr->next;
        free(curr->errmsg);
        free(curr);
        curr = next;
    }
}
/*End Functions*/