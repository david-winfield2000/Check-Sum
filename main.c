#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    // printf("%s %s %s\n------\n", argv[0], argv[1], argv[2]);

    int size = atoi(argv[2]);

    // printf("size = %d", size);

    if (!(size == 8 || size == 16 || size == 32)) {
        fprintf(stderr, "Valid chesksum sizes are 8, 16, or 32\n");
        return 0;
    }

    // printf("working with size: %d", size);

    FILE *file;
    file = fopen(argv[1], "r");




    fclose(file);

    return 0;
}
