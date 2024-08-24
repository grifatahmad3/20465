/* Necessary declarations and definitons needed for the first pass phase. */
#ifndef FIRSTPASSH
#define FIRSTPASSH

#include "essentials.h"

Bool startFirstPass(char* filename, Macro **macros, ERR **err, Symbol **symbols, int *IC, int *DC, MachineCode **inst, MachineCode **data);

#endif