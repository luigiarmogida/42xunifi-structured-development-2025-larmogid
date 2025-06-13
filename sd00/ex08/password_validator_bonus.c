#include <string.h>
#include "password_validator.h"

PwStatus validate_password(const char *new_pw, PasswordHistory *history) {
	if (!is_strong(new_pw))
		return INVALID_WEAK;

	for (int i = 0; i < history->count; i++) {
		if (edit_distance(new_pw, history->passwords[i]) <= 1)
			return INVALID_SIMILAR;
	}

	// Aggiungi la password nuova nella lista
	strncpy(history->passwords[history->index], new_pw, MAX_PASSWORD_LENGTH);
	history->passwords[history->index][MAX_PASSWORD_LENGTH] = '\0'; // sicuro
	history->index = (history->index + 1) % HISTORY_SIZE;
	if (history->count < HISTORY_SIZE)
		history->count++;

	return VALID;
}

/* 
int main(void) {
	PasswordHistory h = { .count = 0, .index = 0 };

	const char *tests[] = {
		"Password1@",     // VALID
		"Password2@",     // INVALID_SIMILAR (edit dist. da "Password1@")
		"Passw0rd4@",     // VALID
		"Pa55word5@",     // VALID
		"NewPass6@",      // VALID → ora "Password1@" è fuori dallo storico
		"Password1@",     // INVALID_SIMILAR? No! ora è fuori, dovrebbe essere VALID
		NULL
	};

	for (int i = 0; tests[i]; i++) {
		PwStatus status = validate_password(tests[i], &h);
		const char *result =
			status == VALID ? "VALID" :
			status == INVALID_WEAK ? "INVALID_WEAK" :
			status == INVALID_SIMILAR ? "INVALID_SIMILAR" : "UNKNOWN";

		printf("Testing \"%s\": %s\n", tests[i], result);
		if (status == VALID)
			print_history(&h);
		printf("----\n");
	}
	return 0;
}
 */