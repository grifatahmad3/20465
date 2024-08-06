/* Implementaions of essentials.h */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "essentials.h"

/*Functions*/

char* addExtToFilename(char* ext, char* fileName, int num){
    char *temp = (char*) malloc(sizeof(char) * MAX_LENGTH);
    strcpy(temp, fileName);
    strncat(temp, ext, num);
    return temp;
}


bool definedMacroName(Macro *head, char* name){
    Macro *temp = (Macro *) malloc(sizeof(Macro));
    temp = head;
    while (temp != NULL)
    {
        if(!strcmp(temp->name, name)){
            free(temp);
            return true;
        }
        temp = head->next;
    }
    free(temp);
    return false;
}

Macro* newMacro(char* name, char* definition, Macro *next){
    Macro *new_macro = (Macro*) malloc(sizeof(Macro));
    strcpy(new_macro->name, name);
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
/*End Functions*/