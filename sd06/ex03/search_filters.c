#include "movie.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Converte una stringa in minuscolo per confronto case-insensitive
void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

void search_movies(t_movie_list *list) {
    if (!list || list->count == 0) {
        printf("No movies loaded.\n");
        return;
    }

    char keyword[256];
    printf("Enter search keyword (title or genre): ");
    scanf(" %[^\n]", keyword);

    char kw_lower[256];
    strncpy(kw_lower, keyword, sizeof(kw_lower));
    kw_lower[sizeof(kw_lower) - 1] = '\0';
    to_lowercase(kw_lower);

    int found = 0;
    t_movie *cur = list->head;
    while (cur) {
        char title_lower[1024], genre_lower[256];
        strncpy(title_lower, cur->title, sizeof(title_lower));
        strncpy(genre_lower, cur->genre, sizeof(genre_lower));
        title_lower[sizeof(title_lower) - 1] = '\0';
        genre_lower[sizeof(genre_lower) - 1] = '\0';
        to_lowercase(title_lower);
        to_lowercase(genre_lower);

        if (strstr(title_lower, kw_lower) || strstr(genre_lower, kw_lower)) {
            print_movie(cur);
            found++;
        }
        cur = cur->next;
    }

    if (!found)
        printf("No match found for \"%s\".\n", keyword);
}


/* seconda parte */
void filter_movies(t_movie_list *list) {
	if (!list || list->count == 0) {
		printf("No movies loaded.\n");
		return;
	}

	int choice;
	printf("Filter by:\n1. Watched\n2. Unwatched\nEnter choice: ");
	if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
		while (getchar() != '\n');
		printf("Invalid choice.\n");
		return;
	}

	int match = 0;
	t_movie *cur = list->head;
	while (cur) {
		if ((choice == 1 && cur->watched == 1) || (choice == 2 && cur->watched == 0)) {
			print_movie(cur);
			match++;
		}
		cur = cur->next;
	}
	if (!match)
		printf("No %s movies found.\n", choice == 1 ? "watched" : "unwatched");
}