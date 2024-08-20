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
#define ILLEGAL_MACRO_NAME "Illegal macro name!\n"
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
#define MAX_OP_LINES 3 /* Maximum number of lines each operation could generate in binary*/
#define IMM_ACCESS 1 /* immediate access: 0001 */
#define DIR_ACCESS 2 /* direct access: 0010 */
#define IND_REG_ACCESS 4 /* indirect register access: 0100 */
#define DIR_REG_ACCESS 8 /* direct register access: 1000 */
#define A_FIELD 4 /* 100 */
#define R_FIELD 2 /* 010 */
#define E_FIELD 1 /* 001 */
#define BITS11_14(x) (x<<11) /* sets the bits 11-14 in the binary */
#define BITS7_10(x) (x<<7) /* as above */
#define BITS3_6(x) (x<<3) /* as above */
#define BITS3_14(x) (x<<3) /* as above */
#define BITS6_8(x) (x<<6) /* as above */
#define BITS3_5(x) (x<<3) /* as above */
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
    int address;
} Symbol;


typedef enum _bool {
    false,
    true
} Bool;


typedef struct _op {
    char* name;
    int opcode;
    int opr_num;
} OP;


typedef struct _err{
    char *errmsg;
    struct _err* next;
    int line_num;
} ERR;
/*End Structs*/

/*Functions*/
    /* Printing number in binary */
void printInBinary(unsigned int num);

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
Bool addERR(ERR **head, char* msg, int line_num);

    /*print all errors*/
void printERR(ERR **head);

    /*frees all allocated errors*/
void freeERR(ERR **head);

/*End Functions*/

#endif