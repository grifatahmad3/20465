/* Implementaions of firstpass.h */

#include <stdio.h>
#include "firstpass.h"
#include "essentials.h"


    /*  The Algorithm
    *
    *   1- set IC=0, DC=0;
    *   2- read next line. if EOF then move on to second pass.
    *   3- is the first field(token) a symbol? if no jump to step 5
    *   4- set flag isSymbol=true;
    *   5- is this data command (.data or .string)?, if no jump to step 8
    *   6- if isSymbol==true, add to symbols with sfor=data and address=DC. if symbol exists, add and err.
    *   7- recognize the type of data (.data or .string?), add to MachineCode **data with address of DC, 
    *       update DC accordingly, and enter with the label symbol for the first line.
    *   8- is this .extern or .entry? if no jump to step 11
    *   9- is this .extern? if yes, add to Symbols with type=ext, sfor=forNone, address=(0+E_FIELD). jump to step 2
    *   10- if isSymbol==true, add to Symbols with 
    *   
    * 
    *   if no errors detected: update IC(address) = IC+100 in MachineCode **inst and Symbol **symbols with sfor=forInst,
    *   update DC = DC+IC in MachineCode **data and **symbols with sfor=forData.
    * 
    *   In 2nd pass, go over all MachineCode **inst and update address of instances with label from Symbol **symbols with sfor=forInst,
    *                go over all MachineCode **data and update address of instances with label from Symbol **symbols with sfor=forData.
    *   If all is good, make all output files with the necessarry format.
    * */

Bool startFirstPass(char* filename, Macro **macros, ERR **err, Symbol **symbols, int *IC, int *DC, MachineCode **inst, MachineCode **data){

    
    return true;
}
