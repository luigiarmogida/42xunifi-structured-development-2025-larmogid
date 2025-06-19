// filters.h
#ifndef FILTERS_H
#define FILTERS_H

#include "movie.h"

void list_all_movies(const t_catalog *catalog);
void search_by_title_or_genre(const t_catalog *catalog, const char *query);
void filter_by_watched(const t_catalog *catalog, int watched);

#endif

// stats.h
#ifndef STATS_H
#define STATS_H

#include "movie.h"

void print_statistics(const t_catalog *catalog);

#endif
