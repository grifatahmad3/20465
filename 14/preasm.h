/* Necessary declarations and definitons needed for the pre-assembler phase. */
#ifndef PREASSMH
#define PREASSMH

#include "essentials.h"

    /*starts the pre assembler stage*/
Bool startPreAsm(char* filename, Macro **macros, ERR **err);

#endif