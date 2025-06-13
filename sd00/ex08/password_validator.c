#include <string.h>
#include "password_validator.h"

static int is_special(char c) {
	const char specials[] = "@#$%^&*";
	for (int i = 0; specials[i]; i++) {
		if (c == specials[i])
			return 1;
	}
	return 0;
}

int is_strong(const char *pw) {
	if (!pw)
		return 0;

	int len = 0;
	int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;

	while (pw[len]) {
		char c = pw[len];
		if (c >= 'A' && c <= 'Z') has_upper = 1;
		else if (c >= 'a' && c <= 'z') has_lower = 1;
		else if (c >= '0' && c <= '9') has_digit = 1;
		else if (is_special(c)) has_special = 1;
		len++;
	}

	if (len < 8 || !has_upper || !has_lower || !has_digit || !has_special)
		return 0;

	return 1;
}

int edit_distance(const char *s1, const char *s2) {
	int len1 = strlen(s1);
	int len2 = strlen(s2);

	if (len1 < len2) {
		const char *tmp = s1; s1 = s2; s2 = tmp;
		int tmp_len = len1; len1 = len2; len2 = tmp_len;
	}

	if (len1 - len2 > 1)
		return 2; // troppo diverse

	int diff = 0, i = 0, j = 0;
	while (s1[i] && s2[j]) {
		if (s1[i] != s2[j]) {
			diff++;
			if (diff > 1)
				return 2;
			if (len1 != len2)
				i++;  // salto solo da s1 (la più lunga)
			else {
				i++; j++;
			}
		} else {
			i++; j++;
		}
	}
	if (s1[i] || s2[j]) diff++;
	return diff;
}

#include <stdio.h>
void print_history(const PasswordHistory *h) {
	printf("Password history:\n");
	for (int i = 0; i < h->count; i++) {
		int idx = (h->index + HISTORY_SIZE - h->count + i) % HISTORY_SIZE;
		printf("  [%d] %s\n", i, h->passwords[idx]);
	}
}
