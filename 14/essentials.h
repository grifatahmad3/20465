/* This files should include all essential declarations and important definitions 
*   that will be needed by most or all files in the project.
*   This includes functions that might be needed by more than one file, 
*   data structures, and so on.
*  Can be split in the future if necessary to multiple files, but as of 08/2024 I see no
*   need to do so as the current split of files makes more sense to me*/

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
#define LINE_TOO_LONG "Overflow: The line is too long!\n"
#define FILE_ERROR "File Error! Can't open or create file!!\n"
#define MACRO_ADD_FAIL "Failed creating a new macro!\n"
#define TOO_MUCH_ARGUMENTS "Too much Arguments! expected less...\n"
#define WORD_FAILED "Failed reading word!\n"
#define ILLEGAL_MACRO_NAME "Illegal macro name!\n"
#define RAM_EMPTY "Out of RAM! No available RAM...\n"
#define ILLEGAL_SYMBOL_NAME "Illegal symbol name!\n"
#define SYMBOL_EXISTS "Symbol with such name already exists!\n"
#define SYMBOL_EMPTY "Illegal! Empty symbol declaration!\n"
#define ILLEGAL_FORMAT "Illegal format!!\n"
#define NUM_OUT_OF_BOUND "The lateral number is out of bounds of what's allowed!\n"
/*End Errors*/


/* Definitions */
#define MAX_LENGTH 100
#define MAX_LINE 81 /* 80 + '\n' */
#define OP_NUM 16
#define RAM_SIZE 4096
#define STARTING_ADDRESS 100
#define WORD_SIZE 15
#define MAX_DATA_NUM 16383 /* 14 bits in 2's complement */
#define MIN_DATA_NUM -16384 /* same as above */
#define MAX_NUMBER 2047 /* 12 bits in 2's complement, as we only have 12 bits for storing numbers*/
#define MIN_NUMBER -2048 /* same as above*/
#define REG_NUM 8
#define MAX_SYMBOL_NAME 31
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
#define DATA ".data"
#define STRING ".string"
#define ENTRY ".entry"
#define EXTERN ".extern"
/*End Definitions*/


/* Structs */
typedef struct _macro { /*to store macros and their definitions*/
    char *name;
    char *definition;
    struct _macro* next;
} Macro;


typedef enum _symbol_type{ /*denoting whether a symbol is entry, extern or none*/
    none,
    ent,
    ext
} SymbolType;

typedef enum _symbol_for{ /*denoting whether it's an instruction symbol or data symbol*/
    forNone, /*used for externals*/
    forInst,
    forData
} SymbolFor;

typedef struct _symbol{ /*used to store the symbol tables*/
    char *name;
    int address;
    SymbolFor sfor;
    SymbolType type;
    struct _symbol* next;
} Symbol;


typedef struct _machine_code{ /*used to store the machine code generated from the files*/
    int code;
    int address;
    char *label; /*optional, used for first pass to know where labels (symbols) should go*/
    struct _machine_code *next;
} MachineCode;


typedef enum _bool { /*true or false*/
    false,
    true
} Bool;


typedef struct _op { /*used to store the language operations, their defined codes, and how many operands they accept*/
    char* name;
    int opcode;
    int opr_num;
} OP;

typedef enum _opr_type{
    noOp,
    imm,
    dir,
    regIndir,
    regDir
} OprType;


typedef struct _err{ /*used to store all generated errors*/
    char *errmsg;
    int line_num;
    struct _err* next;
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
OP* findOP(const char *str);

    /*Check whether the given string is a register or not*/
int findReg(const char *str);

    /*Makes and returns a new macro based on user input*/
Bool addMacro(Macro **head, char* name, char* definition);

    /*Adds definition to a given macro, assumes macro already exists*/
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

    /*finds if a symbol already exists and returns its address, NULL if it doesn't exist*/
Symbol* findSymbol(Symbol **head, char *name);

    /*creates a new symbol, assumes symbol with the same name doesn't exist*/
Bool addSymbol(Symbol **head, char *name, int address, SymbolFor sfor, SymbolType type);

    /*adds an address to an existsing symbol, assumes the symbol already exists*/
Bool addSymbolAddress(Symbol *smbl, int address);

    /*frees all allocated space for symbols*/
void freeSymbols(Symbol **head);

    /*adds a new MachineCode instance*/
Bool addMachineCode(MachineCode **head, int code, int address, char* label);

    /*finds a machinecode instance via the given address, returns NULL if not found*/
MachineCode* findMCAddress(MachineCode **head, int address);

    /*returns the machinecode instance that has a matching label, NULL otherwise*/
MachineCode* findMCLabel(MachineCode **head, char *label);

    /*adds binary code to a given MachineCode instance*/
Bool addCodeToMC(MachineCode *mc, int code);

    /*frees all allocated space for MachineCode*/
void freeMCs(MachineCode **head);

    /*checks whether a symbol name is legal or not, does not check whether the symbol exists or not!*/
Bool isLegalSymbolName(char *name);

    /* prints the symbols list*/
void printSymbols(Symbol **head);

    /* prints the machinecode list*/
void printMachineCode(MachineCode **head);

    /*checks whether it's a legal operand name and find its type*/
OprType findOprType(char *token);
/*End Functions*/

    /*frees all struct if they exist*/
void freeAllStructs(ERR **err, Macro **macros, Symbol **symbols, MachineCode **inst, MachineCode **data);


#endif