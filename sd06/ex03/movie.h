#ifndef MOVIE_H
# define MOVIE_H

# include <stdlib.h>

typedef struct s_movie {
	int id;
	char *title;
	char *genre;
	int watched;
	int rating;
	char *date;
	struct s_movie *next;
}	t_movie;

typedef struct s_movie_list {
	t_movie *head;
	int max_id;
	int count;
}	t_movie_list;

// Main functions
t_movie_list	*init_movie_list(void);
void			load_movies(const char *filename, t_movie_list *list);
void			free_movie_list(t_movie_list *list);

// Helpers
char			*trim_whitespace(char *str);
int				is_valid_date(const char *date);
int				is_duplicate_id(t_movie_list *list, int id);

void			print_movie(t_movie *m); // 👈 AGGIUNTA QUI
void			list_movies_sorted(t_movie_list *list);
void			search_movies(t_movie_list *list);
void			filter_movies(t_movie_list *list);
void			add_movie(t_movie_list *list);
void			mark_watched(t_movie_list *list);
void			update_movie(t_movie_list *list);
void			delete_movie(t_movie_list *list);
void			show_statistics(t_movie_list *list);
void			save_movies(const char *filename, t_movie_list *list);

#endif
