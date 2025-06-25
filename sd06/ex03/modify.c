#include "input_utils.h"
#include "movie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_movie(t_movie_list *list) {
	char title[256], genre[256], date[16];
	int watched = 0, rating = 0;
	char buffer[256];

	printf("Enter title: ");
	fgets(title, sizeof(title), stdin);
	title[strcspn(title, "\n")] = '\0';
	if (strlen(title) == 0) {
		printf("Title cannot be empty.\n");
		return;
	}

	printf("Enter genre: ");
	fgets(genre, sizeof(genre), stdin);
	genre[strcspn(genre, "\n")] = '\0';
	if (strlen(genre) == 0) {
		printf("Genre cannot be empty.\n");
		return;
	}

	printf("Watched? (0 = No, 1 = Yes): ");
	fgets(buffer, sizeof(buffer), stdin);
	watched = atoi(buffer);
	if (watched != 0 && watched != 1) {
		printf("Invalid watched value.\n");
		return;
	}

	if (watched == 1) {
		printf("Enter rating (1-10): ");
		fgets(buffer, sizeof(buffer), stdin);
		rating = atoi(buffer);
		if (rating < 1 || rating > 10) {
			printf("Invalid rating.\n");
			return;
		}

		printf("Enter date watched (YYYY-MM-DD): ");
		fgets(date, sizeof(date), stdin);
		date[strcspn(date, "\n")] = '\0';
		if (!is_valid_date(date)) {
			printf("Invalid date format.\n");
			return;
		}
	} else {
		rating = 0;
		strcpy(date, "");
	}

	t_movie *new = malloc(sizeof(t_movie));
	if (!new) {
		perror("malloc failed");
		return;
	}
	new->id = ++list->max_id;
	new->title = strdup(title);
	new->genre = strdup(genre);
	new->watched = watched;
	new->rating = rating;
	new->date = strdup(date);
	new->next = list->head;
	list->head = new;
	list->count++;

	printf("Movie \"%s\" added with ID %d.\n", title, new->id);
}

/* parte 2 */

void mark_watched(t_movie_list *list) {
	if (!list || list->count == 0) {
		printf("No movies loaded.\n");
		return;
	}

	char buffer[256], date[16];
	int id, rating;

	printf("Enter the ID of the movie to mark as watched: ");
	fgets(buffer, sizeof(buffer), stdin);
	id = atoi(buffer);

	t_movie *cur = list->head;
	while (cur && cur->id != id)
		cur = cur->next;

	if (!cur) {
		printf("Movie with ID %d not found.\n", id);
		return;
	}

	if (cur->watched == 1) {
		printf("Movie \"%s\" is already marked as watched.\n", cur->title);
		return;
	}

	printf("Enter rating (1-10): ");
	fgets(buffer, sizeof(buffer), stdin);
	rating = atoi(buffer);
	if (rating < 1 || rating > 10) {
		printf("Invalid rating.\n");
		return;
	}

	printf("Enter date watched (YYYY-MM-DD): ");
	fgets(date, sizeof(date), stdin);
	date[strcspn(date, "\n")] = '\0';
	if (!is_valid_date(date)) {
		printf("Invalid date format.\n");
		return;
	}

	cur->watched = 1;
	cur->rating = rating;
	free(cur->date);
	cur->date = strdup(date);

	printf("Movie \"%s\" marked as watched.\n", cur->title);
}

/* parte 3 */

void update_movie(t_movie_list *list) {
	if (!list || list->count == 0) {
		printf("No movies loaded.\n");
		return;
	}

	char new_title[256], new_genre[256];
	int id = input_int("Enter the ID of the movie to update (0 to cancel): ", 0, list->max_id);

	t_movie *cur = list->head;
	while (cur && cur->id != id)
		cur = cur->next;

	if (!cur) {
		printf("Movie with ID %d not found.\n", id);
		return;
	}

	printf("Current movie:\n");
	print_movie(cur);

	printf("Enter new title (leave blank to keep current): ");
	fgets(new_title, sizeof(new_title), stdin);
	new_title[strcspn(new_title, "\n")] = '\0';
	if (strlen(new_title) > 0) {
		free(cur->title);
		cur->title = strdup(new_title);
	}

	printf("Enter new genre (leave blank to keep current): ");
	fgets(new_genre, sizeof(new_genre), stdin);
	new_genre[strcspn(new_genre, "\n")] = '\0';
	if (strlen(new_genre) > 0) {
		free(cur->genre);
		cur->genre = strdup(new_genre);
	}

	printf("Movie updated successfully.\n");
}

/* parte 4 */

void delete_movie(t_movie_list *list) {
	if (!list || list->count == 0) {
		printf("No movies loaded.\n");
		return;
	}

	char buffer[256];
	int id;

	printf("Enter the ID of the movie to delete: ");
	fgets(buffer, sizeof(buffer), stdin);
	id = atoi(buffer);

	t_movie *cur = list->head;
	t_movie *prev = NULL;

	while (cur && cur->id != id) {
		prev = cur;
		cur = cur->next;
	}

	if (!cur) {
		printf("Movie with ID %d not found.\n", id);
		return;
	}

	printf("Selected movie:\n");
	print_movie(cur);

	printf("Are you sure you want to delete this movie? (y/n): ");
	fgets(buffer, sizeof(buffer), stdin);
	if (buffer[0] != 'y' && buffer[0] != 'Y') {
		printf("Cancelled.\n");
		return;
	}

	if (!prev)
		list->head = cur->next;
	else
		prev->next = cur->next;

	free(cur->title);
	free(cur->genre);
	free(cur->date);
	free(cur);
	list->count--;

	printf("Movie deleted.\n");
}
