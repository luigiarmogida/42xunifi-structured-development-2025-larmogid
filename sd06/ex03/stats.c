#include "movie.h"
#include <stdio.h>
#include <string.h>

typedef struct s_genre_stats {
	char genre[64];
	int watched_count;
	int unwatched_count;
	struct s_genre_stats *next;
} t_genre_stats;

static t_genre_stats *get_genre(t_genre_stats **head, const char *name) {
	t_genre_stats *cur = *head;
	while (cur) {
		if (strcmp(cur->genre, name) == 0)
			return cur;
		cur = cur->next;
	}
	t_genre_stats *new = malloc(sizeof(t_genre_stats));
	strcpy(new->genre, name);
	new->watched_count = 0;
	new->unwatched_count = 0;
	new->next = *head;
	*head = new;
	return new;
}

void show_statistics(t_movie_list *list) {
	if (!list || list->count == 0) {
		printf("No movies loaded.\n");
		return;
	}

	int total = list->count;
	int watched = 0, unwatched = 0;
	int sum_rating = 0, rated_count = 0;
	t_genre_stats *genres = NULL;

	t_movie *cur = list->head;
	while (cur) {
		if (cur->watched) {
			watched++;
			sum_rating += cur->rating;
			rated_count++;
		} else {
			unwatched++;
		}
		t_genre_stats *g = get_genre(&genres, cur->genre);
		if (cur->watched)
			g->watched_count++;
		else
			g->unwatched_count++;
		cur = cur->next;
	}

	printf("\n=== Watchlist Statistics ===\n");
	printf("Total movies: %d\n", total);
	printf("Watched: %d\n", watched);
	printf("Unwatched: %d\n", unwatched);
	if (rated_count)
		printf("Average rating (watched): %.2f\n", (double)sum_rating / rated_count);
	else
		printf("Average rating: N/A\n");

	printf("\nBy genre:\n");
	t_genre_stats *g = genres;
	while (g) {
		printf("Genre: %s | Watched: %d | Unwatched: %d\n", g->genre, g->watched_count, g->unwatched_count);
		t_genre_stats *tmp = g;
		g = g->next;
		free(tmp); // pulizia
	}
}
