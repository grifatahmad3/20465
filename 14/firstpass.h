/* Necessary declarations and definitons needed for the first pass phase. */
#ifndef FIRSTPASSH
#define FIRSTPASSH

#include "essentials.h"

Bool is_number(char *str);
Bool parse_line_data(char *line, int *array, size_t *size);
Bool parse_line_string(char *line, int *array, size_t *size);
Bool startFirstPass(char* filename, Macro **macros, ERR **err, Symbol **symbols, int *IC, int *DC, MachineCode **inst, MachineCode **data);

#endif