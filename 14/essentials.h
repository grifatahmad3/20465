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
    char name[MAX_LENGTH];
    char definition[MAX_LENGTH];
    struct _macro* next;
} Macro;

typedef struct _symbol{
    char name[MAX_LENGTH];
} Symbol;


typedef enum _bool {
    false,
    true
} bool;


typedef struct _op {
    char* name;
    int opcode;
} op;


typedef struct _err{
    char *errmsg;
    struct _err* next;
} err;
/*End Structs*/

/*Functions*/

    /*Adds the needed file extension to the file name*/
char* addExtToFilename(char* ext, char* fileName, int num);

    /*Checks whether the macro was defined before or not*/
bool isMacro(Macro *head, char* name);


    /*Checks whther the given string is an operation or not*/
bool isOP(char *str);


    /*Makes and returns a new macro based on user input*/
Macro* newMacro(char* name, char* definition, Macro *next);


    /*prints the macros*/
void printMacros(Macro* head);

/*End Functions*/

#endif