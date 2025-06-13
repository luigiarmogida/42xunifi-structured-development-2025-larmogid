#include "password_validator.h"

static int is_special(char c) {
    // const char specials[] = { 0x40, 0x23, 0x24, 0x25, 0x5E, 0x26, 0x2A, '\0' };
    //                            @     #     $     %     ^     &     *
    const char specials[] = { '@', '#', '$', '%', '^', '&', '*', '\0' }; // const char *specials = "@#$%^&*";
	for (int i = 0; specials[i]; i++) {
		if (c == specials[i])
			return 1;
	}
	return 0;
}

PwStatus validate_password(const char *new_pw, const char *curr_pw) {
	if (!new_pw || !curr_pw)
		return INVALID;

	int len = 0;
	int has_upper = 0;
	int has_lower = 0;
	int has_digit = 0;
	int has_special = 0;

	while (new_pw[len]) {
		char c = new_pw[len];
		if (c >= 'A' && c <= 'Z')
			has_upper = 1;
		else if (c >= 'a' && c <= 'z')
			has_lower = 1;
		else if (c >= '0' && c <= '9')
			has_digit = 1;
		else if (is_special(c))
			has_special = 1;
		len++;
	}

	if (len < 8 || !has_upper || !has_lower || !has_digit || !has_special)
		return INVALID;

	// Confronto con password corrente
	for (int i = 0; new_pw[i] || curr_pw[i]; i++) {
		if (new_pw[i] != curr_pw[i])
			return VALID;
	}
	return INVALID; // Sono identiche
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