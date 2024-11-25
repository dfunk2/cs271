// InvalidLabel.asm
// This file tests invalid label detection.

@2D
D=M
(#INVALID_LABEL)  // Invalid label with non-alphabetic starting character.
@LOOP
0;JMP

