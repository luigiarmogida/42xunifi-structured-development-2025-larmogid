#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

#define MAX_PASSWORD_LENGTH 100
#define HISTORY_SIZE 3

typedef enum {
	VALID,
	INVALID_WEAK,
	INVALID_SIMILAR
} PwStatus;

typedef struct {
	char passwords[HISTORY_SIZE][MAX_PASSWORD_LENGTH + 1];
	int count;
	int index;
} PasswordHistory;

/* Core API */

// Coordina la validazione di una nuova password
// verificando prima la forza e poi la similarità con lo storico
PwStatus validate_password(const char *new_pw, PasswordHistory *history);

/* Strength rules */
int is_strong(const char *pw);
int is_long_enough(const char *pw);
int has_uppercase(const char *pw);
int has_lowercase(const char *pw);
int has_digit(const char *pw);
int has_special(const char *pw);

/* Similarity rules */
// Funzione di supporto: scorre lo storico e verifica se la nuova password 
// è troppo simile (edit distance ≤ 1) a una delle ultime accettate.
int is_similar_to_history(const char *pw, const PasswordHistory *history);
// Implementazione ottimizzata della distanza di Levenshtein: calcola se due 
// stringhe hanno distanza 0, 1 o >1 con uscita anticipata
int edit_distance(const char *s1, const char *s2); // ottimizzata per dist <= 1

/* History update */
// Gestisce l'inserimento della nuova password nello storico circolare, 
// sovrascrivendo la più vecchia se necessario.
void update_password_history(const char *pw, PasswordHistory *history);

#endif