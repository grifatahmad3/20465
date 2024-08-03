#include <stdio.h>
#include "essentials.h"

int main(int argc, char *argv[]){
   
    int i = 0;
    while(i < argc){
        printf(PREASSM_START);
        /*start preassm*/
        printf(PREASSM_END);
        i++;
    }

    return 0;
}