// load_movies.c

#include "input_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

#define MAX_LINE_LEN 1024

// Funzione per duplicare stringa con trimming
char *trim_and_strdup(char *str) {
	str = trim_whitespace(str);
	if (!str || *str == '\0')
		return NULL;
	return strdup(str);
}

static int	parse_line(char *line, t_movie_list *list) {
	char *fields[6];
	int i = 0;
	char *token = strtok(line, ",");

	while (token && i < 6)
		fields[i++] = trim_whitespace(token), token = strtok(NULL, ",");

	if (i != 6) {
		fprintf(stderr, "Warning: invalid field count\n");
		return 0;
	}

	int id = atoi(fields[0]);
	if (id <= 0 || is_duplicate_id(list, id)) {
		fprintf(stderr, "Warning: invalid or duplicate ID\n");
		return 0;
	}

	char *title = trim_and_strdup(fields[1]);
	char *genre = trim_and_strdup(fields[2]);
	if (!title || !genre) {
		fprintf(stderr, "Warning: empty title or genre\n");
		free(title);
		free(genre);
		return 0;
	}

	int watched = atoi(fields[3]);
	if (watched != 0 && watched != 1) {
		fprintf(stderr, "Warning: invalid watched flag\n");
		free(title);
		free(genre);
		return 0;
	}

	int rating = atoi(fields[4]);
	char *date = strdup(fields[5]);

	if (watched == 1) {
		if (rating < 1 || rating > 10 || !is_valid_date(date)) {
			fprintf(stderr, "Warning: invalid rating or date\n");
			free(title); free(genre); free(date);
			return 0;
		}
	} else {
		rating = 0;
		free(date);
		date = strdup("");
	}

	// Aggiungi alla lista
	t_movie *new = malloc(sizeof(t_movie));
	new->id = id;
	new->title = title;
	new->genre = genre;
	new->watched = watched;
	new->rating = rating;
	new->date = date;
	new->next = list->head;
	list->head = new;
	list->count++;
	if (id > list->max_id)
		list->max_id = id;

	return 1;
}

void load_movies(const char *filename, t_movie_list *list) {
	FILE *fp = fopen(filename, "r");
	if (!fp) {
		perror("Error opening file");
		return;
	}

	char line[1024];
	while (fgets(line, sizeof(line), fp)) {
		// Rimuove newline finale se presente
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';

		// Salta righe vuote
		if (line[0] == '\0')
			continue;

		// Passa la linea al parser
		if (!parse_line(line, list))
			fprintf(stderr, "Skipped line: %s\n", line);
	}

	fclose(fp);
}
