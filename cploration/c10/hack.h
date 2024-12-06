#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#ifndef __HACK_H__
#define __HACK_H__
#define NUM_PREDEFINED_SYMBOLS 23
#define INST_A Atype_instruction
#define INST_C Ctype_instruction


typedef enum {
    SP = 0,
    LCL = 1,
    ARG = 2,
    THIS = 3,
    THAT = 4,
    R0 = 0,
    R1 = 1,
    R2 = 2,
    R3 = 3, 
    R4 = 4, 
    R5 = 5,
    R6 = 6,
    R7 = 7,
    R8 = 8,
    R9 = 9,
    R10 = 10,
    R11 = 11,
    R12 = 12,
    R13 = 13,
    R14 = 14,
    R15 = 15,
    SCREEN = 16384,
    KBD = 24576,

}symbol_id;

typedef struct{
    char name[7];
    int16_t address;

}predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"SP", 0},
    {"LCL", 1},
    {"ARG", 2},
    {"THIS", 3},
    {"THAT", 4},
    {"R0", 0}, 
    {"R1", 1}, 
    {"R2", 2},
    {"R3", 3},
    {"R4", 4},
    {"R5", 5},
    {"R6", 6},
    {"R7", 7},
    {"R8", 8},
    {"R9", 9},
    {"R10", 10},
    {"R11", 11},
    {"R12", 12},
    {"R13", 13},
    {"R14", 14},
    {"R15", 15},
    {"SCREEN", 16384},
    {"KBD", 24576},
};

typedef enum {
    JMP_INVALID = -1,
    JMP_NULL = 0,
    JGT =1,
    JEQ =2,
    JGE =3,
    JLT =4,
    JNE =5,
    JLE =6,
    JMP =7, 
}jump_id;

typedef enum {
    DEST_INVALID = -1,
    DEST_NULL =0,
    M =1, 
    D =2, 
    MD =3,
    A =4,
    AM =5,
    AD =6,
    AMD =7,  
}dest_id;

typedef enum {
    COMP_INVALID = -1,
    COMP_0 = 42, 
    COMP_1 = 63,
    COMP_2 = 58,
    COMP_3 = 12,

    COMP_4 = 48,
    COMP_5 = 13,

    COMP_6 = 49,
    COMP_7 = 15,

    COMP_8 = 51, 
    COMP_9 = 31,

    COMP_10 = 55, 
    COMP_11 = 14,

    COMP_12 = 50,

    COMP_13 = 2,
    COMP_14 = 19,
    COMP_15 = 7,
    COMP_16 = 0,
    COMP_17 = 21,
/*--------- a bit is 1 ------------*/
    COMP_18 = 48,
    COMP_19 = 49,
    COMP_20 = 51,
    COMP_21 = 55,
    COMP_22 = 50,

    COMP_23 = 2,
    COMP_24 = 19,
    COMP_25 = 7,
    COMP_26 = 0,
    COMP_27 = 21,

}comp_id;

static inline jump_id str_to_jumpid(const char *s) {
    jump_id id = JMP_INVALID;   
    if (s == NULL) {
        id = JMP_NULL;
    }else if (strcmp(s, "JGT") == 0) {
        id = JGT;
    } else if (strcmp(s, "JEQ") == 0){
        id = JEQ;
    } else if(strcmp(s, "JGE") == 0) {
        id = JGE;
    } else if(strcmp(s, "JLT")==0){
        id = JLT;
    } else if(strcmp(s, "JNE")==0){
        id = JNE;
    }else if(strcmp(s, "JLE")==0){
        id = JLE;
    } else if (strcmp(s, "JMP")==0) {
        id = JMP;
    }
    return id;
}
static inline dest_id str_to_destid(const char *s){
    dest_id id = DEST_INVALID;
    if(s == NULL){
        id = DEST_NULL;
    }else if (strcmp(s, "M")==0){
        id = M; 
    }else if(strcmp(s, "D")==0){
        id =D;
    }else if(strcmp(s, "MD")==0){
        id = MD;
    }else if(strcmp(s, "A")==0){
        id = A;
    }else if(strcmp(s, "AM")==0){
        id = AM;
    }else if(strcmp(s, "AD")==0){
        id = AD;
    }else if(strcmp(s, "AMD")==0){
        id = AMD;
    }
    return id;
}
static inline comp_id str_to_compid(const char *s, int *a) {
    comp_id id = COMP_INVALID;
    *a = 0;
    if(strcmp(s, "0")==0){
        id = COMP_0;
    }else if(strcmp(s, "1")==0){
        id =COMP_1;
    }else if(strcmp(s, "-1")==0){
        id = COMP_2;
    }else if(strcmp(s, "D")==0){
        id = COMP_3;
    }else if(strcmp(s, "A")==0){
        id = COMP_4;
    }else if(strcmp(s, "!D")==0){
        id = COMP_5;
    }else if(strcmp(s, "!A")==0){
        id = COMP_6;
    }else if (strcmp(s, "-D")==0){
        id = COMP_7; 
    }else if(strcmp(s, "-A")==0){
        id = COMP_8;
    }else if(strcmp(s, "D+1")==0){
        id = COMP_9;
    }else if(strcmp(s, "A+1")==0){
        id = COMP_10;
    }else if(strcmp(s, "D-1")==0){
        id = COMP_11;
    }else if(strcmp(s, "A-1")==0){
        id = COMP_12;
    }else if(strcmp(s, "D+A")==0){
        id = COMP_13;
    }else if (strcmp(s, "D-A")==0){
        id = COMP_14; 
    }else if(strcmp(s, "A-D")==0){
        id =COMP_15;
    }else if(strcmp(s, "D&A")==0){
        id = COMP_16;
    } else if(strcmp(s, "D|A")==0){
        id = COMP_17;

    }else if(strcmp(s, "M")==0){
        id = COMP_18;
        *a = 1;
    }else if(strcmp(s, "!M")==0){
        id = COMP_19;
        *a = 1;
    }else if (strcmp(s, "-M")==0){
        id = COMP_20; 
        *a = 1;
    }else if(strcmp(s, "M+1")==0){
        id = COMP_21;
        *a = 1;
    }else if(strcmp(s, "M-1")==0){
        id = COMP_22;
        *a = 1;
    }else if(strcmp(s, "D+M")==0){
        id = COMP_23;
        *a = 1;
    }else if(strcmp(s, "D-M")==0){
        id = COMP_24;
        *a = 1;
    }else if(strcmp(s, "M-D")==0){
        id = COMP_25;
        *a = 1;
    }else if(strcmp(s, "D&M")==0){
        id = COMP_26;
        *a = 1;
    }else if(strcmp(s, "D|M")==0){
        id = COMP_27;
        *a = 1;
    }

    return id;
}
#endif