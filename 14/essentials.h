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
#define FILE_ERROR "File Error! Can't open file!!"
/*End Errors*/


/* Definitions */
#define MAX_LENGTH 100
#define MAX_LINE 82 /* 80 + '\n' + '\0' */
#define OP_NUM 16
#define EXT_ORIGIN ".as"
#define EXT_PREASM ".am"
#define EXT_OBJECT ".ob"
#define EXT_ENTRIES ".ent"
#define EXT_EXTERNALS ".ext"
/*End Definitions*/


/* Structs */
typedef struct _macro {
    char *name;
    char *definition;
    struct _macro* next;
} Macro;

typedef struct _symbol{
    char *name;
} Symbol;


typedef enum _bool {
    false,
    true
} Bool;


typedef struct _op {
    char* name;
    int opcode;
} OP;


typedef struct _err{
    char *errmsg;
    struct _err* next;
} ERR;
/*End Structs*/

/*Functions*/

    /*Adds the needed file extension to the file name*/
char* addExtToFilename(char* ext, char* fileName, int num);

    /*Checks whether the macro was defined before or not*/
Bool isMacro(Macro *head, char* name);


    /*Checks whether the given string is an operation or not*/
Bool isOP(char *str);


    /*Makes and returns a new macro based on user input*/
Macro* newMacro(char* name, char* definition, Macro *next);


    /*prints the macros*/
void printMacros(Macro* head);

    /*adds an error message to error node*/
Bool addERR(ERR **head, char* msg);

    /*print all errors*/
void printERR(ERR **head);

    /*frees all allocated errors*/
void freeERR(ERR **head);
/*End Functions*/

#endif