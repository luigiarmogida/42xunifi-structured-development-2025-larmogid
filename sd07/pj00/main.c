#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

#define INPUT_LEN 128

void display_menu(void)
{
	printf("\n=== MOVIE WATCHLIST MENU ===\n\n");
	printf("1. Show all movies\n");
	printf("2. Filter by genre\n");
	printf("3. Add a movie\n");
	printf("4. Save to file\n");
	printf("5. Delete a movie by title\n");
	printf("6. Sort movies by year\n");
	printf("7. Exit\n");
	printf("Select an option: ");
}


int main(void)
{
	t_movie *watchlist = load_movies("movies.csv");
	if (!watchlist)
		printf("No movies loaded. Starting with empty watchlist.\n");

	char input[INPUT_LEN];
	int running = 1;

	while (running)
	{
		display_menu();
		if (!fgets(input, INPUT_LEN, stdin))
			break;

		int option = atoi(input);
		switch (option)
		{
			case 1:
				print_movies(watchlist);
				break;
			case 2:
				printf("Enter genre to filter: ");
				if (fgets(input, INPUT_LEN, stdin))
				{
					input[strcspn(input, "\n")] = '\0';
					filter_by_genre(watchlist, input);
				}
				break;
			case 3:
			{
				char title[INPUT_LEN], genre[INPUT_LEN];
				int year;
				float rating;

				printf("Enter title: ");
				fgets(title, INPUT_LEN, stdin);
				title[strcspn(title, "\n")] = '\0';

				printf("Enter genre: ");
				fgets(genre, INPUT_LEN, stdin);
				genre[strcspn(genre, "\n")] = '\0';

				printf("Enter year: ");
				fgets(input, INPUT_LEN, stdin);
				year = atoi(input);

				printf("Enter rating: ");
				fgets(input, INPUT_LEN, stdin);
				rating = atof(input);

				watchlist = add_movie(watchlist, title, genre, year, rating);
				break;
			}
			case 4:
				save_movies(watchlist, "movies.csv");
				break;
            case 5:
            {
                char title[INPUT_LEN];
                printf("Enter title to delete: ");
                if (fgets(title, INPUT_LEN, stdin))
                {
                    title[strcspn(title, "\n")] = '\0';
                    watchlist = delete_movie(watchlist, title);
                }
                break;
            }
            case 6:
                sort_by_year(&watchlist);
                printf("\nMovies sorted by year:\n\n");
				print_movies(watchlist);
                break;
            case 7:
                running = 0;
                break;
			default:
				printf("Invalid option. Try again.\n");
		}
	}

	free_movies(watchlist);
	printf("Goodbye!\n");
	return 0;
}
