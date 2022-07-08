#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// // Function that prints 80 characters per line
// void print80(char *str)
// {
// 	for (int i = 0; i < strlen(str); i++)
// 	{
// 		if (i % 80 == 0)
// 			printf("\n");
// 		printf("%c",str[i]);
// 	}
// }

// // Calculate 8 bit checksum from the input string
// unsigned long int calc8bit(char *input)
// {
// 	int result = 0;
// 	for (int i = 0; i < strlen(input); i++)
// 	{
// 		result += input[i];
// 	}

// 	return result;
// }

// // Calculate 16 bit checksum from the input string
// unsigned long int calc16bit(char *input)
// {
// 	int res16bit = 0;
// 	for (int i = 0; i < strlen(input);)
// 	{
// 		res16bit += input[i] << 8;
// 		res16bit += (input[i + 1]);
// 		i+=2;
// 	}

// 	return res16bit;
// }

// // Calculate 32 bit checksum from the input string
// unsigned long int calc32bit(char *input)
// {
// 	unsigned long int res32bit = 0;
// 	for (int i = 0; i < strlen(input);)
// 	{
// 		res32bit += input[i] << 24;
// 		res32bit += (input[i + 1]) << 16;
// 		res32bit += (input[i + 2]) << 8;
// 		res32bit += (input[i + 3]);
// 		i+=4;
// 	}
	
// 	return res32bit;
// }

void printAnswer(char *input, int bitsize, int ans) {

	printf("%s\n", input);
	printf("%2d bit checksum is %8lx for all %4d chars\n", bitsize, ans, (int)strlen(input));

	return;
}

char *readFile(FILE *file, char *input) {
	char c;
    int length = 0;

    while ((c = fgetc(file)) != EOF) {
        input[length++] = c;
        input = realloc(input, length + 1);
    }

	input[length] = '\0';

	return input;
}

void checksum8(char *input) {
	int ans = 0;

	for (int i = 0; i < strlen(input); i++)
	{
		ans += input[i];
	}

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

	// printf("Padded input string: %s\n", input);

	int ans = 0;
	for (int i = 0; i < strlen(input); i)
	{
		ans += input[i] << 8;
		ans += (input[i + 1]);
		i += 2;
	}

	printAnswer(input, 16, ans & 0xFFFF);

	return;
}

void checksum32(char *input) {

	// Pad with multiple X's if necessary
	while (strlen(input) % 4) {
		input[strlen(input)] = 'X';
		input = malloc(strlen(input) + 1);
	}
	// Add terminating character to end of string
	input[strlen(input)] = '\0';

	int ans = 0;

	for (int i = 0; i < strlen(input); i++)
	{
		ans += input[i] << 24;
		ans += (input[i + 1]) << 16;
		ans += (input[i + 2]) << 8;
		ans += (input[i + 3]);
		i += 4;
	}

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
	// printf("Input string: %s\n", input);

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