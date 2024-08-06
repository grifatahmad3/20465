
#include "preasm.h"
#include "essentials.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool startPreAsm(char* filename){
    char str[MAX_LENGTH];
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp==NULL)
        return false;
    while (fgets(str, MAX_LENGTH, fp) != NULL){
        printf("%s", str);
    }
    fclose(fp);
    printf("\n\n");
    return true;
}