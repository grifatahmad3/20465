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


/* Constants */
#define MAX_LENGTH 100
/*End Constants*/


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

    /*prints the macros*/
void printMacros(Macro* head);

/*End Functions*/

#endif