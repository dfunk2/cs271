/****************************************
 * C-ploration 4 for CS 271
 * 
 * Denise Funk
 * Fall 2024
 * 
 ****************************************/
#include "parser.h"

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
void parse(FILE * file){
	char line[MAX_LINE_LENGTH];
	char label[MAX_LABEL_LENGTH];

	unsigned int line_number = 0;
	unsigned int instr_num = 0;
	instruction instr;

	add_predefined_symbols();
	

	while(fgets(line, sizeof(line), file)) 
	{	
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
			} 

			else if (is_Ctype(line)) {
				inst_type = 'C';
		}
			//printf("%u: %c  %s\n", instr_num, inst_type, line);
			instr_num++;
	}

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
//parse an A instruction
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
