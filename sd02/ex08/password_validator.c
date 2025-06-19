/* ************************************************************************** */
/*                            password_validator.c                            */
/* ************************************************************************** */

#include <string.h>
#include "password_validator.h"

static int is_special(char c) {
	const char *specials = "@#$%^&*";
	for (int i = 0; specials[i]; i++) {
		if (c == specials[i])
			return 1;
	}
	return 0;
}

int is_long_enough(const char *pw) {
	int len = 0;
	while (pw[len])
		len++;
	return len >= 8;
}

int has_uppercase(const char *pw) {
	for (int i = 0; pw[i]; i++) {
		if (pw[i] >= 'A' && pw[i] <= 'Z')
			return 1;
	}
	return 0;
}

int has_lowercase(const char *pw) {
	for (int i = 0; pw[i]; i++) {
		if (pw[i] >= 'a' && pw[i] <= 'z')
			return 1;
	}
	return 0;
}

int has_digit(const char *pw) {
	for (int i = 0; pw[i]; i++) {
		if (pw[i] >= '0' && pw[i] <= '9')
			return 1;
	}
	return 0;
}

int has_special(const char *pw) {
	for (int i = 0; pw[i]; i++) {
		if (is_special(pw[i]))
			return 1;
	}
	return 0;
}

int is_strong(const char *pw) {
	return is_long_enough(pw) && has_uppercase(pw) && has_lowercase(pw)
		&& has_digit(pw) && has_special(pw);
}

/* 
#include <stdio.h>

int main(void) {
	const char *current = "Password1@";
	const char *good =    "BetterP@ss2";
	const char *bad =     "short1@";
	const char *same =    "Password1@";

	printf("Valid? %d (expected 0)\n", validate_password(good, current));
	printf("Valid? %d (expected 1)\n", validate_password(bad, current));
	printf("Valid? %d (expected 1)\n", validate_password(same, current));
    printf("Valid? %d (expected 1)\n", validate_password(same, current));

}
*/