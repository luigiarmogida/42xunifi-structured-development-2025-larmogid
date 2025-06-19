#ifndef PARSE_H
#define PARSE_H

#include "watchlist.h"

// Carica il file CSV e riempie la MediaList
// Ritorna 0 se ok, -1 in caso di errore critico
int load_watchlist(MediaList *list, const char *filename);

// Salva la lista nel file, usando il nuovo formato esteso
// Ritorna 0 se ok, -1 in caso di errore
int save_watchlist(const MediaList *list, const char *filename);

// Funzione di log per righe malformate (internamente usata)
void log_warning(const char *message, const char *line);

#endif
