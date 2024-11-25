#include "error.h"
#include "parser.h"
#include "symtable.h"

const char *error_messages[] = {
    [EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]", //initializer that maps to message
    [EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s", 
    [EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than the maximum of %u instructions.",
    [EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name",
    [EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined",
    [EXIT_INVALID_A_INSTR] = "Line %u: %s : Invalid A-instruction operand",
};

void exit_program(enum exitcode code, ...) //enum exitcode takes enum value code
{
    va_list arguments; //type stores variable arguments
    va_start(arguments, code); //initializes the argument list, allows acess to variables after code

    printf("ERROR: ");
    /*prints va_list, stdout is output, 
    err.mess[code] retrieves error message corresponding to the code. If
    the code is Exit_INCORRECT_ARGUMENTS, it will fetch message. Arguments is list of variable arguments.  */
    vfprintf(stdout, error_messages[code], arguments); 
    printf("\n");

    va_end(arguments); //frees resourses used by the variable arguments.
    exit(code);
}