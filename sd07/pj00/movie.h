// movie.h

#ifndef MOVIE_H
# define MOVIE_H

typedef struct s_movie {
	char *title;
	char *genre;
	int year;
	float rating;
	struct s_movie *next;
} t_movie;

// Caricamento e salvataggio
t_movie *load_movies(const char *filename);
void save_movies(t_movie *head, const char *filename);

// Visualizzazione e gestione
void print_movies(t_movie *head);
void filter_by_genre(t_movie *head, const char *genre);
t_movie *add_movie(t_movie *head, const char *title, const char *genre, int year, float rating);
t_movie *delete_movie(t_movie *head, const char *title);

// Ordinamento
void sort_by_year(t_movie **head);

// Utilità
void free_movies(t_movie *head);
char *strdup_safe(const char *s);

#endif
