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


void printMacros(Macro *head){
    while(head != NULL){
        printf("Macro:\n");
        printf("%s", head->name);
        printf("\n");
        printf("%s", head->definition);
        printf("\n\n");
        head = head->next;
    }
}
/*End Functions*/