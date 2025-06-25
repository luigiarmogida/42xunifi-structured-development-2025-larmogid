#include "input_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input_string(const char *prompt, char *buffer, size_t size) {
	printf("%s", prompt);
	if (fgets(buffer, size, stdin)) {
		buffer[strcspn(buffer, "\n")] = '\0';
	} else {
		buffer[0] = '\0';
	}
}

// Ritorna un intero valido tra min e max (inclusi)
int input_int(const char *prompt, int min, int max) {
	char buffer[64];
	int value;
	char *endptr;

	while (1) {
		if (prompt)
			printf("%s", prompt);
		if (!fgets(buffer, sizeof(buffer), stdin)) {
			clearerr(stdin);
			continue;
		}
		buffer[strcspn(buffer, "\n")] = '\0';

		if (buffer[0] == '\0') {
			printf("Input cannot be empty. Try again.\n");
			continue;
		}

		value = strtol(buffer, &endptr, 10);
		if (*endptr != '\0') {
			printf("Invalid number. Try again.\n");
			continue;
		}
		if (value < min || value > max) {
			printf("Number must be between %d and %d.\n", min, max);
			continue;
		}
		return value;
	}
}