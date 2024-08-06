/* Implementaions of essentials.h */

#include <stdio.h>
#include "essentials.h"

/*Functions*/
void printMacros(Macro *head){
    while(head != NULL){
        printf("Macro:\n");
        printf(head->name);
        printf("\n");
        printf(head->definition);
        printf("\n\n");
        head = head->next;
    }
}
/*End Functions*/