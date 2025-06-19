/* ************************************************************************** */
/*                         password_validator_bonus.c                         */
/* ************************************************************************** */

#include <string.h>
#include "password_validator.h"

PwStatus validate_password(const char *new_pw, PasswordHistory *history) {
	if (!new_pw || !history)
		return INVALID_WEAK;

	if (!is_strong(new_pw))
		return INVALID_WEAK;

	if (is_similar_to_history(new_pw, history))
		return INVALID_SIMILAR;

	update_password_history(new_pw, history);
	return VALID;
}

/* 
	scorre lo storico e verifica se la nuova password è troppo simile 
	(edit distance ≤ 1) a una delle ultime accettate 
*/
int is_similar_to_history(const char *pw, const PasswordHistory *history) {
	for (int i = 0; i < history->count; i++) {
		if (edit_distance(pw, history->passwords[i]) <= 1)
			return 1;
	}
	return 0;
}

/* 
	Implementazione ottimizzata della distanza di Levenshtein, 
	calcola se due stringhe hanno distanza 0, 1 o >1 con uscita anticipata.
*/
int edit_distance(const char *s1, const char *s2) {
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return 999; // considerato lontanissimo

	if (s1 && s2 && strcmp(s1, s2) == 0)
		return 0;

	if (abs(len1 - len2) > 1)
		return 2;

	int diffs = 0;
	int i = 0, j = 0;
	while (s1[i] && s2[j]) {
		if (s1[i] != s2[j]) {
			diffs++;
			if (diffs > 1)
				return 2;
			if (len1 > len2)
				i++;
			else if (len2 > len1)
				j++;
			else {
				i++;
				j++;
			}
		} else {
			i++;
			j++;
		}
	}
	if (s1[i] || s2[j])
		diffs++;

	return diffs;
}

/* 
	Gestisce l'inserimento della nuova password nello storico circolare, 
	sovrascrivendo la più vecchia se necessario 
*/
void update_password_history(const char *pw, PasswordHistory *history) {
	strncpy(history->passwords[history->index], pw, MAX_PASSWORD_LENGTH);
	history->passwords[history->index][MAX_PASSWORD_LENGTH] = '\0';
	history->index = (history->index + 1) % HISTORY_SIZE;
	if (history->count < HISTORY_SIZE)
		history->count++;
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