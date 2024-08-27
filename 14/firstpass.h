/* Necessary declarations and definitons needed for the first pass phase. */
#ifndef FIRSTPASSH
#define FIRSTPASSH

#include "essentials.h"

Bool isNumber(char *str);
Bool parseLineData(char *line, int *array, size_t *size);
Bool parseLineString(char *token, int *array, size_t *size);
Bool proccessInstLine(ERR **err, MachineCode **inst, int *IC, char *token, Bool inSymbol, char *symbolName, Symbol **symbols, int line_num);
Bool parseTwoOperands(char *token, char *word1, char *word2);
Bool startFirstPass(char* filename, Macro **macros, ERR **err, Symbol **symbols, int *IC, int *DC, MachineCode **inst, MachineCode **data);

#endif