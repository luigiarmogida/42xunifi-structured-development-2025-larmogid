#ifndef HISTORY_OPS_H
#define HISTORY_OPS_H

#include "watchlist.h"

// Aggiunge una visione all'item (TV/Anime usano season/episode)
// Se movie, season/episode devono essere 0
int add_viewing(MediaItem *item, const char *date, int rating, int season, int episode);

// Stampa tutta la cronologia dell'item
void print_history(const MediaItem *item);

// Calcola il rating medio, ritorna -1 se nessuna visione
float compute_average_rating(const MediaItem *item);

#endif