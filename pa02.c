#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void printAnswer(char *input, int bitsize, int ans) {

	int counter = 0;
	char c;

	// Stop when terminating character read
	while ((c = input[counter]) != '\0') {
		if (counter % 80 == 0) {
			printf("\n");
		}

		printf("%c", input[counter++]);
	}

	printf("\n");

	printf("%2d bit checksum is %8lx for all %4d chars\n", (int)bitsize, (long unsigned int)ans, strlen(input));

	return;
}

char *readFile(FILE *file, char *input) {
	char c;
    int length = 0;

    while ((c = fgetc(file)) != EOF) {
        input[length++] = c;
        input = realloc(input, length + 1);
    }

	// Add terminating character to string
	input[length] = '\0';

	return input;
}

void checksum8(char *input) {

	int length = strlen(input);

	// Calculate the checksum using algorithm for size 8
	int ans = 0;

	for (int i = 0; i < length; i++)
	{
		ans += input[i];
	}

	// Print answer using given format, cast the checksum with given 8 bit size
	printAnswer(input, 8, ans & 0xFF);

	return;
}

void checksum16(char *input) {

	int length = strlen(input); 

	// Pad with X as necessary
	if (strlen(input) % 2) {
		input[length++] = 'X';
        input = realloc(input, length + 1);
	}

	// Add terminating character to end of string
	input[length] = '\0';

	// Calculate the checksum using algorithm for size 16
	int ans = 0;

	for (int i = 0; i < strlen(input); i)
	{
		ans += input[i] << 8;
		ans += (input[i + 1]);
		i += 2;
	}

	// Print answer using given format, cast the checksum with given 16 bit size
	printAnswer(input, 16, ans & 0xFFFF);

	return;
}

void checksum32(char *input) {

	int length = strlen(input);

	// Pad with multiple X's if necessary
	while (length % 4) {
		input[length++] = 'X';
        input = realloc(input, length + 1);
	}

	// Add terminating character to end of string
	input[length] = '\0';

	// Calculate the checksum using algorithm for size 32
	int ans = 0;

	for (int i = 0; i < strlen(input); i)
	{
		ans += input[i] << 24;
		ans += (input[i + 1]) << 16;
		ans += (input[i + 2]) << 8;
		ans += (input[i + 3]);
		i += 4;
	}

	// Print answer using given format, cast the checksum with given 32 bit size
	printAnswer(input, 32, ans & 0xFFFFFFFF);
	
	return;
}

int main(int argc, char **argv)
{
	// ---------------- Parse input file ----------------

    // Open file
    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "File could not be opened\n");
        return 0;
    }

	// Read second argument to get bit bitsize
    int bitsize = atoi(argv[2]);

    // Force user to enter correct bitsize
    if (!(bitsize == 8 || bitsize == 16 || bitsize == 32)) {
        fprintf(stderr, "Valid chesksum bitsizes are 8, 16, or 32\n");
        return 0;
    }

	// Create character array and create space for first character
	char *input;
	input = malloc(1);

	// Fill character array with data from input file
	input = readFile(file, input);

	// Close input file
	fclose(file);

	// ---------------- Calculate checksum ----------------

	switch (bitsize)
	{
	case 8:
		checksum8(input);
		break;
	case 16:
		checksum16(input);
		break;
	case 32:
		checksum32(input);
		break;
	default:
		break;
	}

	return 0;
}