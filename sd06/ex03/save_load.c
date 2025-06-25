#include "movie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_by_id(const void *a, const void *b) {
	t_movie *ma = *(t_movie **)a;
	t_movie *mb = *(t_movie **)b;
	return ma->id - mb->id;
}

void save_movies(const char *filename, t_movie_list *list) {
	if (!filename || !list) return;

	FILE *fp = fopen(filename, "w");
	if (!fp) {
		perror("Failed to open file for writing");
		return;
	}

	// Copia i film in un array temporaneo per ordinarli
	t_movie **arr = malloc(sizeof(t_movie *) * list->count);
	if (!arr) {
		perror("malloc failed");
		fclose(fp);
		return;
	}
	t_movie *cur = list->head;
	int i = 0;
	while (cur) {
		arr[i++] = cur;
		cur = cur->next;
	}
	qsort(arr, list->count, sizeof(t_movie *), compare_by_id);

	// Scrive le righe nel formato CSV originale
	for (i = 0; i < list->count; i++) {
		t_movie *m = arr[i];
		fprintf(fp, "%d,%s,%s,%d,%d,%s\n",
			m->id,
			m->title,
			m->genre,
			m->watched,
			m->watched ? m->rating : 0,
			m->watched ? m->date : ""
		);
	}

	free(arr);
	fclose(fp);
	printf("Watchlist saved to \"%s\".\n", filename);
}
