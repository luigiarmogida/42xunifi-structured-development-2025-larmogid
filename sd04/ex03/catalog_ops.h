// catalog_ops.h
#ifndef CATALOG_OPS_H
#define CATALOG_OPS_H

#include "movie.h"

void init_catalog(t_catalog *catalog);
void free_catalog(t_catalog *catalog);
int  add_movie(t_catalog *catalog, const t_movie *movie);
int  delete_movie(t_catalog *catalog, int id);
t_movie *find_movie_by_id(t_catalog *catalog, int id);
void update_movie(t_movie *movie, const char *new_title, const char *new_genre);
void mark_movie_watched(t_movie *movie, int rating, const char *date);

#endif
