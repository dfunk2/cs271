/****************************************
 * C-ploration 4 for CS 271
 * 
 * Denise Funk
 * Fall 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	
	char s_new[strlen(s) + 1];
	int i = 0;

	for (char *s2 = s; *s2; s2++) //temp pointer *s2 which is equal to the original string. Using a copy.
	{
		if (*s2 == '/' && *(s2 + 1) == '/') { 
			break;
		}
		else if (!isspace(*s2)) {
			s_new[i++] = *s2;
		}
	}
		s_new[i] = '\0';
		strcpy(s, s_new);
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
int parse(FILE * file, instruction *instructions) {
	char line[MAX_LINE_LENGTH];
	char label[MAX_LABEL_LENGTH];
	char tmp_line[MAX_LINE_LENGTH];

	unsigned int line_number = 0;
	unsigned int instr_num = 0;
	instruction instr;

	add_predefined_symbols();


	while(fgets(line, sizeof(line), file)) {	
		line_number++;
		if(instr_num > MAX_INSTRUCTIONS) {
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS +1);
		}
		strip(line);
		if (*line == '\0') {
			continue;
		} 
		char inst_type = ' ';
		
		if(is_label(line)){
			inst_type = 'L';
			extract_label(line, label); //extract label
			
			if(!isalpha(label[0])) {
				exit_program(EXIT_INVALID_LABEL, line_number, extract_label(line, label));
			}
			
			strcpy(line, label); //Replace line w/label
			
			if(symtable_find(label)) {
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_number, line);
			}

			symtable_insert(label, instr_num);
			continue;
		}
			else if (is_Atype(line)) {
				inst_type = 'A';
				if (!parse_A_instruction(line, &instr.instr.a)){
    				exit_program(EXIT_INVALID_A_INSTR, line_number, line);
				 }
 				instr.itype = INST_A;

				if(instr.instr.a.is_addr) {
					printf("A: %d\n", instr.instr.a.address);
				} else {
					printf("A: %s\n", instr.instr.a.label);
				}
				
			} 

			else if (is_Ctype(line)) {
				inst_type = 'C';
				strcpy(tmp_line, line);
				parse_C_instruction(tmp_line, &instr.instr.c);

				if(instr.instr.c.dest == DEST_INVALID) {
					exit_program(EXIT_INVALID_C_DEST, line_number, line);
				}
				if(instr.instr.c.comp == COMP_INVALID) {
				exit_program(EXIT_INVALID_C_COMP, line_number, line);
				}
				if(instr.instr.c.jump == JMP_INVALID) {
				exit_program(EXIT_INVALID_C_JUMP, line_number, line);
				}
				
				instr.itype = INST_C;	
				printf("C: d=%d, c=%d, j=%d\n", instr.instr.c.dest, instr.instr.c.comp, instr.instr.c.jump);
			}
			//printf("%u: %c  %s\n", instr_num, inst_type, line);
		instructions[instr_num++] = instr;
	}
	return instr_num;
}
/* Function: is_Atype
----------------------
* Determine if our input string is an A-type instruction or not.
* parameter line is the name of the input argument
*find the first character of line, if it is @ then return true, else return false*/
bool is_Atype(const char *line) {
	return line[0] == '@';

 }
 /*Function: is_label
 ----------------------
 *Determine if the input string is a proper label. 
 * A label starts and ends with ()*/
 
bool is_label(const char *line) {
	size_t len = strlen(line);
	return len > 1 && line[0] == '(' && line[len-1] == ')';
}
/*Function: is_Ctype
---------------------
*Determine if the input string is c-type instruction */
bool is_Ctype(const char *line) {
	if(line[0] == '@' || line[0] == '(') {
		return false;
	}
	for(size_t i = 0; line[i] != '\0'; i++){
		if(!isspace((unsigned char)line[i])){
			return true;
		}
	}
	return false;
}

/*Function that takes a line and extracts the label name from the parenthesis*/
char *extract_label(const char *line, char* label) {
	if(!is_label(line)) {
		return NULL;
	}
	size_t len = strlen(line);
	strncpy(label, line + 1, len-2);
	label[len-2] = '\0';
	
	return label;
}
//load the predefined symbols
void add_predefined_symbols() {
	for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
		predefined_symbol symbol = predefined_symbols[i];
		symtable_insert(symbol.name, symbol.address);

	}
}
//parse A instruction
/*---------------------------------------------------------------------------*/
bool parse_A_instruction(const char *line, a_instruction *instr) {
	char *s = malloc(strlen(line));
	strcpy(s, line+1);
	char *s_end = NULL;
	long result = strtol(s, &s_end, 10);

//valid label
	if(s == s_end) { 
		instr->label = malloc(strlen(s) +1);
		strcpy(instr->label, s);
		instr->is_addr = false;

		} //mixture of letters and numbers, invalid
		else if (*s_end != 0) { 
			free(s);
			return false;
		} //number, valid address
			else {
				instr->address = (hack_addr)result;
				instr->is_addr = true;
			}
			free(s);
			return true;
}
//parse C instruction
/*---------------------------------------------------------------------*/
void parse_C_instruction(char *line, c_instruction *instr) {
	
//tokenize the line by semicolon to separate comp and jump and account for NULL jump
	char *comp_part = strtok(line, ";"); 
	char *jump_part = strtok(NULL, ";");
//tokenize the comp_part by equals sign to separate dest and comp and account for NULL dest
	char *dest_part = strtok(comp_part, "=");
	char *comp = strtok(NULL, "=");
//if there is no comp, then the part before the = is comp
	if(comp == NULL){
		comp = dest_part; //no separate dest part
		dest_part = NULL;
	}
//dest field
	instr->dest = (dest_part != NULL) ? str_to_destid(dest_part) : DEST_NULL;
//comp field
	unsigned int a = 0;
	instr->comp = (comp != NULL) ? str_to_compid(comp, &a) : COMP_INVALID;
//a field
	instr->a = a;
	
//jump field
	instr->jump = (jump_part != NULL) ? str_to_jumpid(jump_part) : JMP_NULL;
}
//assembly function
/*---------------------------------------------------------------------*/
void assemble(const char * file_name, instruction* instructions, int num_instructions){	
	add_predefined_symbols();
	//open output file with .hack suffix
	char output_file[256];
	snprintf(output_file, sizeof(output_file), "%s.hack", file_name);
	FILE *fout = fopen(output_file, "w");
	if(fout == NULL) {
		exit_program(EXIT_CANNOT_OPEN_FILE, file_name);
	}
	
	//iterate over instructions
	for(int i = 0; i < num_instructions; i++) {
		instruction instr = instructions[i];
		struct Symbol *sym = symtable_find(instr.instr.a.label);
		//A instruction
		if(instr.itype == INST_A) {
			opcode op = 0;
			if(instr.instr.a.is_addr) {
				op = instr.instr.a.address;
			} else { 
				//predefined symbol
				sym = symtable_find(instr.instr.a.label);
				if(sym == NULL) {
					static int next_addr = 16;
					symtable_insert(instr.instr.a.label, next_addr);
					//free memory for the label in the instruction...Causes program to output segmentation fault
					free(instr.instr.a.label);
					instr.instr.a.label = NULL;
					next_addr++;
				} else {
				op = sym->addr;
				}
			}
			// Print the 16-bit opcode as a binary string and write to file
			for (int j = 15; j >= 0; j--) {
				fprintf(fout, "%c", (op & (1 << j)) ? '1' : '0');
			}
			fprintf(fout, "\n");
			
			}
			//C instruction
			else if(instr.itype == INST_C) {
					opcode op = instruction_to_opcode(instr.instr.c);
				// Print the 16-bit opcode as a binary string and write to file
        			for (int j = 15; j >= 0; j--) {
                		fprintf(fout, "%c", (op & (1 << j)) ? '1' : '0');
            		}
            		fprintf(fout, "\n");
			}
		
		}
		
		fclose(fout);
		
}
//instruction to opcode function
/*--------------------------------------------------------------*/
opcode instruction_to_opcode(c_instruction instr){
	opcode op = 0;
	//3 most sig bits are 111
	op |= (7 << 13);
	//a
	op |= (instr.a << 12); 
	//comp
	op |= (instr.comp << 6);
	//dest
	op |= (instr.dest << 3);
	//JMP
	op |= (instr.jump << 0);
	return op;
}
