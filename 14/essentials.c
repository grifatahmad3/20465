/* Implementaions of essentials.h */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "essentials.h"

/*Objects*/

OP operations[OP_NUM] = {
    {"mov", 0},
    {"cmp", 1},
    {"add", 2},
    {"sub", 3},
    {"lea", 4},
    {"clr", 5},
    {"not", 6},
    {"inc", 7},
    {"dec", 8},
    {"jmp", 9},
    {"bne", 10},
    {"red", 11},
    {"prn", 12},
    {"jsr", 13},
    {"rts", 14},
    {"stop", 15}
};


/*End Objects*/

/*Functions*/

char* addExtToFilename(char* ext, char* fileName, int num){
    char *temp = (char*) malloc(sizeof(char) * MAX_LENGTH);
    strcpy(temp, fileName);
    strncat(temp, ext, num);
    return temp;
}

Bool isOP(char *str){
    int i;
    for(i = 0; i<OP_NUM; i++){
        if(strcmp(str, operations[i].name) != 0)
            return false;
    }
    return true;
}

Bool isMacro(Macro **head, char* name){
    Macro *temp;
    temp = *head;
    while (temp != NULL)
    {
        if(!strcmp(temp->name, name)){
            return true;
        }
        temp = temp->next;
    }
    return false;
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

Bool addERR(ERR **head, char* msg){
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
        printf("\n%s\n", temp->errmsg);
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