#ifndef STATS_H
#define STATS_H

#include "watchlist.h"

// Stampa le statistiche generali
void print_statistics(const MediaList *list);

// Ricerca per sottostringa in titolo o genere (case-insensitive)
void search_by_substring(const MediaList *list, const char *substr);

#endif