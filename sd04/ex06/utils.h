#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <string.h>

// Rimuove whitespace iniziali e finali (modifica in-place)
void trim_whitespace(char *str);

// Controlla che la data sia nel formato YYYY-MM-DD
int validate_date(const char *date);

// Controlla che il rating sia tra 1 e 10
int validate_rating(int rating);

// Controlla che season e episode siano > 0
int validate_season_episode(int season, int episode);

#endif