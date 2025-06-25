#include "movie_utils.h"
#include <stdio.h>

void print_movie(t_movie *m) {
	printf("ID: %d | \"%s\" | Genre: %s | Watched: %s",
		m->id, m->title, m->genre, m->watched ? "Yes" : "No");
	if (m->watched)
		printf(" | Rating: %d | Date: %s", m->rating, m->date);
	printf("\n");
}
