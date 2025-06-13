#include <stdlib.h>
#include "movie_planner.h"

// Dichiarazioni delle funzioni fornite (sono solo usate, non definite)
struct Preferences *get_user_preferences(void);
struct MovieList   *find_movies(struct Preferences *prefs);
struct Plan        *build_plan(struct MovieList *list);

struct Plan *create_movie_night_plan(void)
{
    struct Preferences *prefs = get_user_preferences();
    if (!prefs)
        return NULL;

    struct MovieList *movies = find_movies(prefs);
    if (!movies) {
        free(prefs); // libero risorsa precedente
        return NULL;
    }

    struct Plan *plan = build_plan(movies);
    if (!plan) {
        free(movies);
        free(prefs);
        return NULL;
    }

    // Cleanup delle strutture non più necessarie (se plan le copia)
    free(movies);
    free(prefs);

    return plan;
}
