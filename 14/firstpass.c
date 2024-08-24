/* Implementaions of firstpass.h */

#include <stdio.h>
#include "firstpass.h"
#include "essentials.h"


    /*  The Algorithm
    *
    *   1- set IC=0, DC=0;
    *   2- read next line. if EOF then jump to 14. if (IC+DC) > (RAM_SIZE-STARTING_ADDRESS) then err.
    *   3- is the first field(token) a symbol? if yes and second token is .entry or .extern jump to 8, or if no jump to step 5
    *   4- set flag isSymbol=true;
    *   5- is this data command (.data or .string)?, if no jump to step 8
    *   6-      if isSymbol==true: - if symbol exists with address!=0, add err.
    *                              - if symbol exists with type=ent, update it with sfor=data and address=DC.
    *                              - if symbol doesn't exist, add to symbols with sfor=data and address=DC and type=none. 
    *                         
    *   7- recognize the type of data (.data or .string?), add to MachineCode **data with address of DC, 
    *       update DC accordingly, and enter with the label symbol for the first line.
    *   8- is this .extern or .entry? if no jump to step 11
    *   9- is this .extern? if yes:
    *                       - if it doesn't exist, add to Symbols with type=ext, sfor=forNone, address=(0+E_FIELD). jump to step 2
    *                       - if it does exist then err.
    *      is this .entry? if yes: 
    *                       - if it does exist with address!=0, update type=ent.
    *                       - if it does exist with address==0, add err. //because it could be either entry but not defined or extern
    *                       - it doesn't exist, add to Symbols with type=ent, sfor=forNone(will be updated when it's found), address=0(unknown).
    *                       
    *                      if other tokens exist then add error. jump to step 2
    * 
    *   10- if isSymbol==true: - if it does exist with address!=0, add err.
    *                          - if it does exist with address==0, update it with sfor=forInst, address=IC, and add the line
    *                                to MachineCode **inst with the first line having label=symbol
    *                          - if it doesn't exist, add to Symbols with sfor=forInst, type=none, address=IC 
    *                               and add the line to MachineCode **inst with the first line having label=symbol
    *   11- search if the first token (maybe second symbol) is an operation. if it's not then err.
    *   12- proccess the line into machine code and calculate how much binary lines are needed (= L).
    *       build the code and add to MachineCode **inst.
    *   13- update IC = IC+L, jump to 2.
    *   14- finished reading the file, if err!=NULL don't go to 2nd stage and print all errs.
    * 
    * 
    *   if no errors detected: update address = address+STARTING_ADDRESS in (MachineCode **inst && Symbol **symbols with sfor=forInst(),
    *                          update IC = IC+STARTING_ADDRESS
    *                          update DC = DC+IC in (MachineCode **data && **symbols with sfor=forData).
    * 
    *   In 2nd pass, go over all MachineCode **inst and update address of instances with label from Symbol **symbols with sfor=forInst,
    *                go over all MachineCode **data and update address of instances with label from Symbol **symbols with sfor=forData.
    *   If all is good, make all output files with the necessarry format.
    * */

Bool startFirstPass(char* filename, Macro **macros, ERR **err, Symbol **symbols, int *IC, int *DC, MachineCode **inst, MachineCode **data){

    
    return true;
}
