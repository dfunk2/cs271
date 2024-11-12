#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.
// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// Add and then put a loop at the end to start over until the number is reached.

int main(int argc, char const *argv[])
{   
int R0 = 9;

int R1 = 9;

int sum = 0;

int i = 1;

while (i <= R0) {
            sum = sum + R1;
            i++;
        }
    
    printf("%d ", sum);
    return sum;
}
