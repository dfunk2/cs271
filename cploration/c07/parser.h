/****************************************
 * C-ploration 4 for CS 271
 * 
 * Denise Funk
 * Fall 2024
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
typedef int16_t hack_addr;
typedef int16_t opcode;

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);
bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
char *extract_label(const char *line, char* label);
enum instr_type {
    Invalid_instruction = -1, 
    Atype_instruction, 
    Ctype_instruction };

typedef struct c_instruction{
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;

};
typedef struct a_instruction{
    union {
        hack_addr address;
        char* label;
        };
    bool is_addr;

};

typedef struct instruction{
    union 
    {
        struct a_instruction;
        struct c_instruction;
    };
    enum instr_type; 
    
};