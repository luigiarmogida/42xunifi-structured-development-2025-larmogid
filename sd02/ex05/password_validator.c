#include "password_validator.h"

#define TRUE 1
#define FALSE 0

static int is_special(char c) {
    // const char specials[] = { 0x40, 0x23, 0x24, 0x25, 0x5E, 0x26, 0x2A, '\0' };
    //                            @     #     $     %     ^     &     *
    const char specials[] = { '@', '#', '$', '%', '^', '&', '*', '\0' }; // const char *specials = "@#$%^&*";
	for (int i = 0; specials[i]; i++) {
		if (c == specials[i])
			return TRUE;
	}
	return FALSE;
}

int is_long_enough(const char *pw) {
    int len = 0;
    while (pw[len])
        len++;
    return (len >= 8);
}

int has_uppercase(const char *pw) {
    for (int i = 0; pw[i]; i++) {
        if (pw[i] >= 'A' && pw[i] <= 'Z')
            return TRUE;
    }
    return FALSE;
}

int has_lowercase(const char *pw) {
    for (int i = 0; pw[i]; i++) {
        if (pw[i] >= 'a' && pw[i] <= 'z')
            return TRUE;
    }
    return FALSE;
}

int has_digit(const char *pw) {
    for (int i = 0; pw[i]; i++) {
        if (pw[i] >= '0' && pw[i] <= '9')
            return TRUE;
    }
    return FALSE;
}

int has_special(const char *pw) {
    for (int i = 0; pw[i]; i++) {
        if (is_special(pw[i]))
            return TRUE;
    }
    return FALSE;
}

int is_different_from_current(const char *new_pw, const char *curr_pw) {
    int i = 0;
    while (new_pw[i] || curr_pw[i]) {
        if (new_pw[i] != curr_pw[i])
            return TRUE;
        i++;
    }
    return FALSE;
}

PwStatus validate_password(const char *new_pw, const char *curr_pw) {
    if (!new_pw || !curr_pw)
        return INVALID;

    if (!is_long_enough(new_pw) ||
        !has_uppercase(new_pw) ||
        !has_lowercase(new_pw) ||
        !has_digit(new_pw) ||
        !has_special(new_pw) ||
        !is_different_from_current(new_pw, curr_pw))
        return INVALID;

    return VALID;
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