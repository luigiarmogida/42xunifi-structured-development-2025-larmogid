#include "movie.h"

t_movie_list *init_movie_list(void) {
	t_movie_list *list = malloc(sizeof(t_movie_list));
	list->head = NULL;
	list->max_id = 0;
	list->count = 0;
	return list;
}

void free_movie_list(t_movie_list *list) {
	t_movie *tmp;
	while (list->head) {
		tmp = list->head->next;
		free(list->head->title);
		free(list->head->genre);
		free(list->head->date);
		free(list->head);
		list->head = tmp;
	}
	free(list);
}
