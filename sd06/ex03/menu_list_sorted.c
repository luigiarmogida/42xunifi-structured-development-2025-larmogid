#include "movie.h"
#include <stdlib.h>
#include <stdio.h>
#include "menu.h"

// Funzione di confronto per qsort
int compare_movies_by_id(const void *a, const void *b) {
    const t_movie *ma = *(const t_movie **)a;
    const t_movie *mb = *(const t_movie **)b;
    return ma->id - mb->id;
}

void list_movies_sorted(t_movie_list *list) {
    if (!list || list->count == 0) {
        printf("No movies to display.\n");
        return;
    }

    // 1. Alloca un array temporaneo
    t_movie **arr = malloc(sizeof(t_movie *) * list->count);
    if (!arr) {
        perror("malloc failed");
        return;
    }

    // 2. Riempilo con i puntatori ai film
    t_movie *cur = list->head;
    int i = 0;
    while (cur) {
        arr[i++] = cur;
        cur = cur->next;
    }

    // 3. Ordina l'array per ID
    qsort(arr, list->count, sizeof(t_movie *), compare_movies_by_id);

    // 4. Stampa i film
    for (i = 0; i < list->count; ++i)
        print_movie(arr[i]);

    // 5. Libera l'array
    free(arr);
}