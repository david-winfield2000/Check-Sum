#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *formatArray(FILE *file, char *input, int bitbitsize);

int getPadding(int lengthOriginal, int bit);

int checksum(char *input, int bit);
int checksum8(char *input);

int main(int argc, char const *argv[])
{
    // Open file
    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "File could not be opened");
        return 0;
    }

    // Read second argument to get bit bitsize
    int bitsize = atoi(argv[2]);

    // Force user to enter correct bitsize
    if (!(bitsize == 8 || bitsize == 16 || bitsize == 32)) {
        fprintf(stderr, "Valid chesksum bitsizes are 8, 16, or 32\n");
        return 0;
    }

    // Create input character array
    char *input = malloc(1);

    // Read all bytes in the file, store as a character array
    input = formatArray(file, input, bitsize);

    // Calculate checksum
    int sum = checksum(input, bitsize);

    // Print statement
    printf("%2d bit checksum is %8lx for all %4d chars\n", bitsize, sum, strlen(input));

    // Close file
    fclose(file);

    return 0;
}

int getPadding(int lengthOriginal, int bit) {
    
    switch (bit)
    {
    case 8:
        return 0;
        break;
    case 16:
        if (lengthOriginal % 2)
            return 1;
        break;
    case 32:
        int i = 0;
        while (lengthOriginal % 4)
            i++;
        return i;
    default:
        break;
    }
}

char *formatArray(FILE *file, char *input, int bitbitsize) {
    char c;
    int length = 0;

    while ((c = fgetc(file)) != EOF) {
        input[length++] = c;
        input = realloc(input, length + 1);
    }

    input[length] = '\0';

    // ---------------------- End of parsing file -------------------- //

    int padding = getPadding(length, bitbitsize);
    int newbitsize;

    newbitsize = length + padding;

    if (padding > 0) {
        for (int j = length; j < newbitsize; j++) {
            input = realloc(input, length++ + 1);
            input[j] = 'X';
        }
    }

    // input[length] = '\0';

    // printf("New string: %s\n", input);
    return input;
}

int checksum(char *input, int bit) {

    int sum;
    switch (bit) {
        case 8:
            sum = checksum8(input);
            break;
        // case 16:
        //     return checksum16(input);
        //     break;
        // case 32:
        //     return checksum32(input);
        //     break;
    }

    return sum & 0xFF;
}

int checksum8(char *input) {
    int check = 0;

    for (int i = 0; i < strlen(input); i++) {
        check += input[i];
    }

    return check;
}

// char *checksum16(char *input) {

// }

// char *checksum32(char *input) {
    
// }