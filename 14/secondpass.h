#ifndef SECONDPASSH
#define SECONDPASSH

#include "essentials.h"

    /*starts the second pass over the symbols and the lines, false if anything failed*/
Bool startSecondPass(char *filename, ERR **err, Symbol **symbols, MachineCode **inst, MachineCode **data, int *IC, int *DC);

#endif