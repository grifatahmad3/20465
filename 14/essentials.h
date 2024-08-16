/* This files should include all essential declarations and important definitions 
*   that will be needed by most or all files in the project.
*   This includes functions that might be needed by more than one file, 
*   data structures, and so on. */

#ifndef ESSENTIALSH
#define ESSENTIALSH


/* Messages */
#define PREASSM_START "Starting Pre-Assembler...\n"
#define PREASSM_END "Pre-Assembler finished successfully!\n"
#define FIRSTPASS_START "Starting stage I of the assembler...\n"
#define FIRSTPASS_END "Assembler stage I finished successfully!\n"
#define SECONDPASS_START "Starting stage II of the assembler...\n"
#define SECONDPASS_END "Assembler stage II finished successfully!\n"
/*End Messages*/

/*Errors*/
#define MALLOC_ERROR "Failed memory allocation!\n"
#define NAME_TOO_LONG "Overflow: The instruction name is too long!\n"
#define FILE_ERROR "File Error! Can't open or create file!!\n"
#define MACRO_ADD_FAIL "Failed creating a new macro!\n"
#define WORD_FAILED "Failed reading word!\n"
/*End Errors*/


/* Definitions */
#define MAX_LENGTH 100
#define MAX_LINE 81 /* 80 + '\n' */
#define OP_NUM 16
#define RAM_SIZE 4096
#define WORD_SIZE 15
#define MAX_NUMBER 2047 /* 12 bits in 2's complement, as we only have 12 bits for storing numbers*/
#define MIN_NUMBER -2048 /* same as above*/
#define REG_NUM 8
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
Macro* findMacro(Macro **head, char* name);

    /*Checks whether the given string is an operation or not*/
int findOP(const char *str);

    /*Check whether the given string is a register or not*/
int findReg(const char *str);

    /*Makes and returns a new macro based on user input*/
Bool addMacro(Macro **head, char* name, char* definition);

    /*Adds definition to a given macro*/
Bool addMacroDefinition(Macro *macro, char* newdef);

    /*prints the macros*/
void printMacros(Macro **head);

    /*frees all allocated macros*/
void freeMacros(Macro **head);

    /*adds an error message to error node*/
Bool addERR(ERR **head, char* msg);

    /*print all errors*/
void printERR(ERR **head);

    /*frees all allocated errors*/
void freeERR(ERR **head);

/*End Functions*/

#endif