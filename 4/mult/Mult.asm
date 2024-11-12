@0
D=M
@3
M=D
@14
D;JEQ
@1
D=M
@2
M=D+M
@3
D=M
@3
M=M-1
D=M
@4
D;JGT
@16
0;JMP
// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.
// Add and then put a loop at the end to start over until the number is reached.
