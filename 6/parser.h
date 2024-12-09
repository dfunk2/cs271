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
#ifndef __PARSER_H__
#define __PARSER_H__
#define MAX_HACK_ADDRESS INT16_MAX 
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

/** function prototypes **/
char *strip(char *s);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
char *extract_label(const char *line, char* label);


typedef enum instr_type {
    Invalid_instruction = -1, 
    Atype_instruction, 
    Ctype_instruction,
 } instr_type;

typedef struct {
    unsigned int a:1;
    opcode comp:7;
    opcode dest:4;
    opcode jump:4;

} c_instruction;

typedef struct {
    union {
        hack_addr address;
        char* label;
        };
    bool is_addr;

} a_instruction;

typedef struct {
    union 
    {
        a_instruction a;
        c_instruction c;
    } instr;
    enum instr_type itype; 
    
}instruction;

int parse(FILE *file, instruction *instructions);
void add_predefined_symbols();
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);
void assemble(const char *filename, instruction *instructions, int num_instructions);
opcode instruction_to_opcode(c_instruction instr);
#endif