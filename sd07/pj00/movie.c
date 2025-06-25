#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

#define LINE_MAX_LEN 512

char *strdup_safe(const char *s)
{
	if (!s)
		return NULL;
	char *dup = malloc(strlen(s) + 1);
	if (dup)
		strcpy(dup, s);
	return dup;
}

void print_movies(t_movie *head)
{
	while (head)
	{
		printf("Title: %s\nGenre: %s\nYear: %d\nRating: %.1f\n---\n",
			head->title, head->genre, head->year, head->rating);
		head = head->next;
	}
}

t_movie *add_movie(t_movie *head, const char *title, const char *genre, int year, float rating)
{
	t_movie *new_node = malloc(sizeof(t_movie));
	if (!new_node)
		return head;

	new_node->title = strdup_safe(title);
	new_node->genre = strdup_safe(genre);
	new_node->year = year;
	new_node->rating = rating;
	new_node->next = NULL;

	if (!head)
		return new_node;

	t_movie *tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return head;
}

t_movie *load_movies(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		perror("Error opening file");
		return NULL;
	}

	char line[LINE_MAX_LEN];
	t_movie *head = NULL;
	t_movie *tail = NULL;

	while (fgets(line, LINE_MAX_LEN, file))
	{
		char *title = strtok(line, ",");
		char *genre = strtok(NULL, ",");
		char *year_str = strtok(NULL, ",");
		char *rating_str = strtok(NULL, "\n");

		if (!title || !genre || !year_str || !rating_str)
			continue;

		t_movie *new_movie = malloc(sizeof(t_movie));
		if (!new_movie)
			continue;

		new_movie->title = strdup_safe(title);
		new_movie->genre = strdup_safe(genre);
		new_movie->year = atoi(year_str);
		new_movie->rating = atof(rating_str);
		new_movie->next = NULL;

		if (!head)
			head = new_movie;
		else
			tail->next = new_movie;
		tail = new_movie;
	}

	fclose(file);
	return head;
}

void filter_by_genre(t_movie *head, const char *genre)
{
	int found = 0;
	while (head)
	{
		if (head->genre && strcmp(head->genre, genre) == 0)
		{
			printf("Title: %s\nGenre: %s\nYear: %d\nRating: %.1f\n---\n",
				head->title, head->genre, head->year, head->rating);
			found = 1;
		}
		head = head->next;
	}
	if (!found)
		printf("No movies found in genre: %s\n", genre);
}

void sort_by_year(t_movie **head)
{
	if (!head || !*head)
		return;

	int swapped;
	t_movie **ptr;
	t_movie *a;
	t_movie *b;

	do {
		swapped = 0;
		ptr = head;

		while ((*ptr) && (*ptr)->next)
		{
			a = *ptr;
			b = a->next;

			if (a->year > b->year)
			{
				// Swap dei nodi
				a->next = b->next;
				b->next = a;
				*ptr = b;

				swapped = 1;
			}
			ptr = &(*ptr)->next;
		}
	} while (swapped);
}


void save_movies(t_movie *head, const char *filename)
{
	FILE *file = fopen(filename, "w");
	if (!file)
	{
		perror("Error saving file");
		return;
	}

	while (head)
	{
		fprintf(file, "%s,%s,%d,%.1f\n",
			head->title, head->genre, head->year, head->rating);
		head = head->next;
	}
	fclose(file);
	printf("Watchlist saved to %s.\n", filename);
}

t_movie *delete_movie(t_movie *head, const char *title)
{
	t_movie *prev = NULL;
	t_movie *curr = head;

	while (curr)
	{
		if (curr->title && strcmp(curr->title, title) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				head = curr->next;

			free(curr->title);
			free(curr->genre);
			free(curr);
			printf("Movie \"%s\" deleted.\n", title);
			return head;
		}
		prev = curr;
		curr = curr->next;
	}
	printf("Movie \"%s\" not found.\n", title);
	return head;
}

void free_movies(t_movie *head)
{
	t_movie *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->title);
		free(tmp->genre);
		free(tmp);
	}
}
