
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "essentials.h"


Bool startSecondPass(char *filename, ERR **err, Symbol **symbols, MachineCode **inst, MachineCode **data, int *IC, int *DC){

    /*
     * The idea behind the algorithm was to not actually need to read the file 2 times, but instead
     * to save all symbols encountered in the symbols table, and if the symbol is not yet known
     * what address will be it be then will be saved with address 0 and updated later when encoutered.
     * Here we check if any symbol stayed with address 0, which would mean it was encountered but had
     * no definition to the address. Otherwise, this will update the correct address in the MachineCode
     * lines to the correct symbol address.
     * Aside from that, this will create the files .ob, .ent, and .ext as needed and prints all the
     * necessary information in them.
     * returns false if a symbol passed first pass with address = 0, or if anything else failed.*/

    char *file_ob, *file_ent, *file_ext;
    FILE *fpr_ob, *fpr_ent, *fpr_ext;
    Bool isob=true, isent=false, isext=false;
    Symbol *temp_symbol;
    MachineCode *temp_mc;
    int ic = *IC - STARTING_ADDRESS, dc = *DC - 1;
    /*(*IC) += STARTING_ADDRESS;*/
    (*DC) +=  ((*IC)-1);

    temp_symbol = *symbols;
    while(temp_symbol!=NULL){
        if(temp_symbol->address == 0){
            printf("Invalid address for symbol: %s\n", temp_symbol->name);
            addERR(err, "Above message!\n", -1);
            return false;
        }
        if(temp_symbol->type == ext){
            isext=true;
            temp_symbol->address = 0+E_FIELD;
        }
        if(temp_symbol->type == ent){
            isent = true;
        }
        /*if(temp_symbol->sfor==forInst){
            temp_symbol->address += STARTING_ADDRESS;
        }*/
        if(temp_symbol->sfor==forData && temp_symbol->type!=ext){
            temp_symbol->address += ((*IC)-1);
        }
        temp_symbol = temp_symbol->next;
    }


    temp_mc = *inst;
    while(temp_mc != NULL){
        if(temp_mc->label != NULL){
            if((temp_symbol=findSymbol(symbols, temp_mc->label)) != NULL){
                if(temp_symbol->type==ext){
                    temp_mc->code=0+E_FIELD;
                }
                if(temp_mc->code==0 && temp_symbol->type!=ext){
                    temp_mc->code = BITS3_14(temp_symbol->address);
                    temp_mc->code +=R_FIELD;
                }
            }
        }
    /*temp_mc->address += STARTING_ADDRESS;*/
    temp_mc = temp_mc->next;
    }
    temp_mc = *data;
    while (temp_mc!=NULL){
        if(temp_mc->label!=NULL){
            if((temp_symbol=findSymbol(symbols, temp_mc->label)) != NULL){
                /*if(temp_mc->code==0){
                    if(temp_symbol->type!=ext){
                        temp_mc->code = BITS3_14(temp_symbol->address);
                        temp_mc->code +=R_FIELD;
                    }
                    else {
                        temp_mc->code = 1;
                    }
                }*/
                if(temp_symbol->type==ext){
                    temp_mc->code=0+E_FIELD;
                }
                if(temp_mc->code==0 && temp_symbol->type!=ext){
                    temp_mc->code = BITS3_14(temp_symbol->address);
                    temp_mc->code +=R_FIELD;
                }
            }
        }

        temp_mc->address += ((*IC)-1);
        temp_mc = temp_mc->next;
    }
    
    if(isob==true){
        file_ob = addExtToFilename(EXT_OBJECT, filename, strlen(EXT_OBJECT));
        if(file_ob==NULL){
            addERR(err, MALLOC_ERROR, -1);
            return false;
        }
        fpr_ob = fopen(file_ob, "w");
        if(fpr_ob==NULL){
            addERR(err, FILE_ERROR, -1);
            free(file_ob);
            return false;
        }
        fprintf(fpr_ob, "%4d %d", ic, dc);
        temp_mc = *inst;
        while(temp_mc!=NULL){
            fprintf(fpr_ob, "\n");
            fprintf(fpr_ob, "%4.4d %.5o", temp_mc->address, temp_mc->code & 077777);
            temp_mc = temp_mc->next;
        }
        temp_mc = *data;
        while(temp_mc!=NULL){
            fprintf(fpr_ob, "\n");
            fprintf(fpr_ob, "%4.4d %.5o", temp_mc->address, temp_mc->code & 077777);
            temp_mc = temp_mc->next;
        }
    }

    if(isext==true){
        file_ext = addExtToFilename(EXT_EXTERNALS, filename, strlen(EXT_EXTERNALS));
        if(file_ext==NULL){
            addERR(err, MALLOC_ERROR, -1);
            if(isob==true){
                free(file_ob);
                fclose(fpr_ob);
            }
            return false;
        }
        fpr_ext = fopen(file_ext, "w");
        if(fpr_ext==NULL){
            addERR(err, FILE_ERROR, -1);
            free(file_ext);
            if(isob==true){
                free(file_ob);
                fclose(fpr_ob);
            }
            return false;
        }

        temp_mc = *inst;
        while(temp_mc!=NULL){
            if(temp_mc->label!=NULL){
                if((temp_symbol = findSymbol(symbols, temp_mc->label))!=NULL && temp_symbol->type==ext){
                    fprintf(fpr_ext, "%s %4.4d\n", temp_symbol->name, temp_mc->address);
                }
            }
            temp_mc=temp_mc->next;
        }

            
    }
    

    if(isent==true){
        file_ent = addExtToFilename(EXT_ENTRIES, filename, strlen(EXT_ENTRIES));
        if(file_ent==NULL){
            addERR(err, MALLOC_ERROR, -1);
            if(isob==true){
                free(file_ob);
                fclose(fpr_ob);
            }
            if(isext==true){
                free(file_ext);
                fclose(fpr_ext);
            }
            return false;
        }
        fpr_ent = fopen(file_ent, "w");
        if(fpr_ent==NULL){
            addERR(err, FILE_ERROR, -1);
            free(file_ent);
            if(isob==true){
                free(file_ob);
                fclose(fpr_ob);
            }
            if(isext==true){
                free(file_ext);
                fclose(fpr_ext);
            }
            return false;
        }
        temp_symbol = *symbols;
        while(temp_symbol!=NULL){
            if(temp_symbol->type==ent){
                fprintf(fpr_ent, "%s %4.4d\n", temp_symbol->name, temp_symbol->address);
            }
            temp_symbol=temp_symbol->next;
        }

    }

    if(isob==true){
        free(file_ob);
        fclose(fpr_ob);
    }
    if(isext==true){
        free(file_ext);
        fclose(fpr_ext);
    }
    if(isent==true){
        free(file_ent);
        fclose(fpr_ent);
    }
    return true;
}