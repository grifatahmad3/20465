/* This files should include all essential declarations and important definitions 
*   that will be needed by most or all files in the project.
*   This includes functions that might be needed by more than one file, 
*   data structures, and so on. */

#ifndef ESSENTIALSH
#define ESSENTIALSH


/* Messages */
#define PREASSM_START "Starting Pre-Assembler...\n"
#define PREASSM_END "Pre-Assembler finished successfully!\n"
/*End Messages*/

/*Errors*/
#define NAME_TOO_LONG "Overflow: The instruction name is too long!"
/*End Errors*/


/* Definitions */
#define MAX_LENGTH 100

typedef enum _bool {
    false,
    true
} bool;
/*End Definitions*/


/* Structs */
typedef struct _macro {
    char name[MAX_LENGTH];
    char definition[MAX_LENGTH];
    struct _macro* next;
} Macro;

typedef struct _symbol{
    char name[MAX_LENGTH];
} Symbol;
/*End Structs*/


/*Functions*/

    /*Adds the needed file extension to the file name*/
char* addExtToFilename(char* ext, char* fileName, int num);

    /*Checks whether the macro was defined before or not*/
bool definedMacroName(Macro *head, char* name);


    /*Makes and returns a new macro based on user input*/
Macro* newMacro(char* name, char* definition, Macro *next);


    /*prints the macros*/
void printMacros(Macro* head);

/*End Functions*/

#endif