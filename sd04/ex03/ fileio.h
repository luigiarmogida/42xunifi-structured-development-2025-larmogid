// fileio.h
#ifndef FILEIO_H
#define FILEIO_H

#include "movie.h"

int     load_movies_from_file(const char *filename, t_catalog *catalog);
int     save_movies_to_file(const char *filename, const t_catalog *catalog);
char    *trim_whitespace(char *str);

#endif
