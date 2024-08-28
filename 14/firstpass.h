/* Necessary declarations and definitons needed for the first pass phase. */
#ifndef FIRSTPASSH
#define FIRSTPASSH

#include "essentials.h"

    /*checks whether a given string is a number or not*/
Bool isNumber(char *str);

    /*parses lines that start with data, false if failed*/
Bool parseLineData(char *line, int *array, size_t *size);

    /*parse lines that start with string, false if failed*/
Bool parseLineString(char *token, int *array, size_t *size);

    /*proccess instruction lines and saves the operands, false if failed*/
Bool proccessInstLine(ERR **err, MachineCode **inst, int *IC, char *token, Bool inSymbol, char *symbolName, Symbol **symbols, int line_num);

    /*parses a line that has two operands and saves the operands, false if failed*/
Bool parseTwoOperands(char *token, char *word1, char *word2);

    /*does the work for the first pass, false if failed*/
Bool startFirstPass(char* filename, Macro **macros, ERR **err, Symbol **symbols, int *IC, int *DC, MachineCode **inst, MachineCode **data);

#endif