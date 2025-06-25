#include "movie.h"
#include "menu.h"
#include "movie_utils.h"
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <csvfile>\n", argv[0]);
		return 1;
	}

	t_movie_list *list = init_movie_list();
	load_movies(argv[1], list);

	printf("Loaded %d valid movies. Max ID = %d\n", list->count, list->max_id);

	interactive_menu(list, argv[1]);

	free_movie_list(list);
	return 0;
}
