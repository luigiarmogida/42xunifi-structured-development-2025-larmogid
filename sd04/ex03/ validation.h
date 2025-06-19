// validation.h
#ifndef VALIDATION_H
#define VALIDATION_H

#include "movie.h"

int is_valid_id(int id, const t_catalog *catalog);
int is_valid_title(const char *title);
int is_valid_genre(const char *genre);
int is_valid_watched(int watched);
int is_valid_rating(int rating);
int is_valid_date(const char *date); // YYYY-MM-DD
int is_duplicate_id(int id, const t_catalog *catalog);

#endif
