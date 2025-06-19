#ifndef UTILS_H
# define UTILS_H

# include "expense_tracker.h"

/*
** Confronta due date: <0 se a < b, 0 se uguali, >0 se a > b.
*/
int     compare_dates(t_date a, t_date b);

/*
** Ritorna una copia della stringa convertita in minuscolo.
*/
char    *to_lowercase(const char *str);

/*
** Verifica se needle è contenuto in haystack (case-insensitive).
*/
bool    string_contains_case_insensitive(const char *haystack, const char *needle);

#endif
