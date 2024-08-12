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

Bool isMacro(Macro *head, char* name){
    Macro *temp; /*= (Macro *) malloc(sizeof(Macro));*/
    temp = head;
    while (temp != NULL)
    {
        if(!strcmp(temp->name, name)){
            free(temp);
            return true;
        }
        temp = temp->next;
    }
    free(temp);
    return false;
}

Macro* newMacro(char* name, char* definition, Macro *next){
    Macro *new_macro = (Macro*) malloc(sizeof(Macro));
    strcpy(new_macro->name, name);
    /* TODO : fix copying the definition*/
    strcpy(new_macro->definition, definition);
    new_macro->next=next;
    return new_macro;
}

void printMacros(Macro *head){
    Macro *temp;
    temp = head;
    while(temp != NULL){
        printf("Macro:\n");
        printf("%s", temp->name);
        printf("\n");
        printf("%s", temp->definition);
        printf("\n\n");
        temp = head->next;
    }
    free(temp);
}

Bool addERR(ERR **head, char* msg){
    ERR *temp;
    temp = *head;
    if(*head == NULL){
        *head = (ERR*)malloc(sizeof(ERR));
        if(*head==NULL){
            printf("\n!!ERR ALLOCATION ERR!!\n");
            return false;
        }
        (*head)->errmsg = (char*) malloc(strlen(msg)+1);
        if((*head)->errmsg==NULL){
            printf("\n!!ERR ALLOCATION ERR!!\n");
            return false;
        }
        strcpy((*head)->errmsg, msg);
        (*head)->next=NULL;
        return true;
    }
    else{
        while(temp->next!=NULL){
            printf("L3");
            temp = temp->next;
        }
        temp->next = (ERR*)malloc(sizeof(ERR));
        if(temp->next==NULL){
            printf("\n!!ERR ALLOCATION ERR!!\n");
            return false;
        }
        temp = temp->next;
        temp->errmsg = (char*) malloc(strlen(msg)+1);
        if(temp->errmsg==NULL){
            printf("\n!!ERR ALLOCATION ERR!!\n");
            return false;
        }
        strcpy(temp->errmsg, msg);
        temp->next=NULL;
        return true;
    }
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