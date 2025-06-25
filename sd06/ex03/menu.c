#include "movie.h"
#include <stdio.h>

void list_movies(t_movie_list *list) {
	if (list->count == 0) {
		printf("No movies to display.\n");
		return;
	}
	t_movie *cur = list->head;
	while (cur) {
		print_movie(cur);
		cur = cur->next;
	}
}

void interactive_menu(t_movie_list *list, const char *filename) {
	char input[16];
	int choice = 0;

	while (1) {
		printf("\n=== Movie Watchlist Menu ===\n\n");
		printf("1. List all movies (sorted)\n");
		printf("2. Search movies\n");
		printf("3. Filter by watched/unwatched\n");
		printf("4. Add new movie\n");
		printf("5. Mark movie as watched\n");
		printf("6. Update movie\n");
		printf("7. Delete movie\n");
		printf("8. Show statistics\n");
		printf("9. Save and Exit\n\n");
		printf("Enter your choice: ");

		// Lettura sicura con fgets + atoi
		if (!fgets(input, sizeof(input), stdin)) {
			printf("Input error.\n");
			continue;
		}

		choice = atoi(input);

		switch (choice) {
			case 1: list_movies_sorted(list); break;
			case 2: search_movies(list); break;
			case 3: filter_movies(list); break;
			case 4: add_movie(list); break;
			case 5: mark_watched(list); break;
			case 6: update_movie(list); break;
			case 7: delete_movie(list); break;
			case 8: show_statistics(list); break;
			case 9:
				save_movies(filename, list);
				printf("Goodbye!\n");
				return;
			default:
				printf("Invalid choice. Try again.\n");
		}
	}
}
