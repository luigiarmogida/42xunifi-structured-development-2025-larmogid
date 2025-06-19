// movie.h
#ifndef MOVIE_H
#define MOVIE_H

typedef struct s_movie
{
	int     id;
	char    *title;
	char    *genre;
	int     watched;        // 0 o 1
	int     rating;         // 1–10 se watched == 1, altrimenti 0
	char    *date_watched;  // stringa YYYY-MM-DD se watched == 1, altrimenti NULL
} t_movie;

typedef struct s_catalog
{
	t_movie *movies;
	int      count;
	int      capacity;
	int      max_id;   // per assegnare nuovi ID
} t_catalog;

#endif
