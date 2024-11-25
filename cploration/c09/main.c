/****************************************
 * C-ploration 4 for CS 271
 * 
 * Denise Funk
 * Fall 2024
 * Synopsis: Makefile with parser.c, parser.h, and main.c
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"

int main(int argc, const char *argv[])
{	//check that one argument has been passed
	if(argc != 2) {
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}
	//open input file
	FILE *fin = fopen(argv[1], "r");

	if(fin == NULL) {
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}
	//Call parse function
	parse(fin);

	symtable_print_labels();
	
	//close file pointer
	fclose(fin);

	return 0;
}


