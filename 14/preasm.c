
#include "preasm.h"
#include "essentials.h"
#include <stdlib.h>
#include <string.h>

void startPreAsm(){
    Macro *new_macro = newMacro("Macro1", "Line1\nLine2\nLine3", NULL);
    printMacros(new_macro);
    if(new_macro!=NULL)
        free(new_macro);
}