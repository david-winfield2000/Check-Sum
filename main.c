#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *formatArray(FILE *file, char *input, int bitsize);

int getPadding(int lengthOriginal, int bit);

int main(int argc, char const *argv[])
{
    // Read second argument to get bit size
    int size = atoi(argv[2]);

    // Force user to enter correct size
    if (!(size == 8 || size == 16 || size == 32)) {
        fprintf(stderr, "Valid chesksum sizes are 8, 16, or 32\n");
        return 0;
    }

    // Open file
    FILE *file;
    file = fopen(argv[1], "r");

    // Create input character array
    char *input = malloc(1);

    // Read all bytes in the file, store as a character array
    input = formatArray(file, input, size);

    // Close file
    fclose(file);

    return 0;
}

int getPadding(int length, int bit) {
    
        int modulus = bit == 32 ? 4 : 2;
        int result = 0;

        while (length % modulus != 0) {
            length++;
            result++;
        }

        return bit > 8 ? result : 0;
}

char *formatArray(FILE *file, char *input, int bitsize) {
    char c;
    int length = 0;

    while ((c = fgetc(file)) != EOF) {
        if (iscntrl(c))
            continue;
        input[length++] = c;
        input = realloc(input, length + 1);
    }

    input[length] = '\0';

    printf("characters read: %d\n", length);
    printf("Original string: %s\n", input);

    // ---------------------- End of parsing file -------------------- //

    int padding = getPadding(length, bitsize);
    int new_length;

    new_length = length + padding;

    if (padding > 0) {
        for (int i = length; i < new_length; i++) {
            input = realloc(input, length + 1);
            input[i] = 'X';
        }
    }

    printf("New string: %s\n", input);

    return input;
}