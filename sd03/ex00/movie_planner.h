#ifndef MOVIE_PLANNER_H
#define MOVIE_PLANNER_H

/* struct Foo;

void test() {
    struct Foo f;           // ❌ Errore: tipo incompleto, non si può istanziare
    struct Foo *p = NULL;   // ✅ OK: solo dichiarazione di puntatore
}
*/

// Forward declarations of incomplete types
struct Preferences;   
struct MovieList;
struct Plan;

struct Plan *create_movie_night_plan(void);

#endif
