// library.c
#include "library.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

static Libro create_book_from_line(char *line) {
    Libro libro;
    char *token;

    // Titolo
    token = strtok(line, ",");
    libro.titolo = strdup(token ? token : "");

    // Autore
    token = strtok(NULL, ",");
    libro.autore = strdup(token ? token : "");

    // Genere
    token = strtok(NULL, ",");
    libro.genere = strdup(token ? token : "");

    // Anno
    token = strtok(NULL, ",");
    libro.anno_pubblicazione = token ? atoi(token) : 0;

    // Numero pagine
    token = strtok(NULL, ",");
    libro.numero_pagine = token ? atoi(token) : 0;

    return libro;
}

static int ensure_capacity(CatalogoLibri *catalogo) {
    if (catalogo->count >= catalogo->capacity) {
        size_t new_capacity = (catalogo->capacity == 0) ? 8 : catalogo->capacity * 2;
        Libro *new_array = realloc(catalogo->libri, new_capacity * sizeof(Libro));
        if (!new_array) return -1;
        catalogo->libri = new_array;
        catalogo->capacity = new_capacity;
    }
    return 0;
}

int load_catalog(const char *filename, CatalogoLibri *catalogo) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    char buffer[BUFFER_SIZE];
    catalogo->libri = NULL;
    catalogo->count = 0;
    catalogo->capacity = 0;

    // Salta intestazione
    if (!fgets(buffer, BUFFER_SIZE, file)) {
        fclose(file);
        return -1;
    }

    while (fgets(buffer, BUFFER_SIZE, file)) {
        // Rimuove newline
        strip_newline(buffer);

        // Salta righe vuote
        if (buffer[0] == '\0' || strspn(buffer, " \t\r") == strlen(buffer))
            continue;

        if (ensure_capacity(catalogo) < 0) {
            fclose(file);
            return -1;
        }

        Libro libro = create_book_from_line(buffer);
        catalogo->libri[catalogo->count++] = libro;
    }

    fclose(file);
    return 0;
}

void free_catalog(CatalogoLibri *catalogo) {
    for (size_t i = 0; i < catalogo->count; ++i) {
        free(catalogo->libri[i].titolo);
        free(catalogo->libri[i].autore);
        free(catalogo->libri[i].genere);
    }
    free(catalogo->libri);
    catalogo->libri = NULL;
    catalogo->count = 0;
    catalogo->capacity = 0;
}

void print_all_books(const CatalogoLibri *catalogo) {
    printf("\n📚 Elenco libri nella Community Digital Library:\n\n");

    for (size_t i = 0; i < catalogo->count; ++i) {
        const Libro *libro = &catalogo->libri[i];
        printf("%zu. \"%s\" di %s [%s, %d] - %d pagine\n",
               i + 1,
               libro->titolo,
               libro->autore,
               libro->genere,
               libro->anno_pubblicazione,
               libro->numero_pagine);
    }

    if (catalogo->count == 0)
        printf("Nessun libro trovato.\n");
}


// Rende minuscola una stringa (alloca nuova)
static char *str_to_lower(const char *str) {
    size_t len = strlen(str);
    char *lower = malloc(len + 1);
    if (!lower) return NULL;

    for (size_t i = 0; i < len; ++i)
        lower[i] = tolower((unsigned char)str[i]);
    lower[len] = '\0';
    return lower;
}

// Cerca substring case-insensitive
static int contains_case_insensitive(const char *text, const char *query) {
    char *text_l = str_to_lower(text);
    char *query_l = str_to_lower(query);
    if (!text_l || !query_l) return 0;

    int found = strstr(text_l, query_l) != NULL;
    free(text_l);
    free(query_l);
    return found;
}

void search_by_title(const CatalogoLibri *catalogo, const char *query) {
    printf("\n🔍 Ricerca per titolo: \"%s\"\n\n", query);
    int found = 0;
    for (size_t i = 0; i < catalogo->count; ++i) {
        const Libro *libro = &catalogo->libri[i];
        if (contains_case_insensitive(libro->titolo, query)) {
            printf("%zu. \"%s\" di %s [%s, %d] - %d pagine\n",
                i + 1,
                libro->titolo,
                libro->autore,
                libro->genere,
                libro->anno_pubblicazione,
                libro->numero_pagine);
            found = 1;
        }
    }
    if (!found)
        printf("Nessun libro trovato.\n");
}

void search_by_author(const CatalogoLibri *catalogo, const char *query) {
    printf("\n🔍 Ricerca per autore: \"%s\"\n\n", query);
    int found = 0;
    for (size_t i = 0; i < catalogo->count; ++i) {
        const Libro *libro = &catalogo->libri[i];
        if (contains_case_insensitive(libro->autore, query)) {
            printf("%zu. \"%s\" di %s [%s, %d] - %d pagine\n",
                i + 1,
                libro->titolo,
                libro->autore,
                libro->genere,
                libro->anno_pubblicazione,
                libro->numero_pagine);
            found = 1;
        }
    }
    if (!found)
        printf("Nessun autore trovato.\n");
}

void print_statistics(const CatalogoLibri *catalogo) {
    printf("\n📊 Statistiche del catalogo:\n\n");

    if (catalogo->count == 0) {
        printf("Nessun libro nel catalogo.\n");
        return;
    }

    int somma_pagine = 0;

    // Mappa generi → contatori (semplificata)
    struct {
        const char *genere;
        int count;
    } generi[100];
    size_t generi_count = 0;

    for (size_t i = 0; i < catalogo->count; ++i) {
        const Libro *libro = &catalogo->libri[i];
        somma_pagine += libro->numero_pagine;

        // Cerca se il genere è già stato registrato
        int trovato = 0;
        for (size_t j = 0; j < generi_count; ++j) {
            if (strcmp(generi[j].genere, libro->genere) == 0) {
                generi[j].count++;
                trovato = 1;
                break;
            }
        }

        // Se non trovato, aggiungilo
        if (!trovato && generi_count < 100) {
            generi[generi_count].genere = libro->genere;
            generi[generi_count].count = 1;
            generi_count++;
        }
    }

    double media = (double)somma_pagine / catalogo->count;
    printf("Totale libri: %zu\n", catalogo->count);
    printf("Media pagine per libro: %.2f\n", media);

    printf("\nLibri per genere:\n");
    for (size_t i = 0; i < generi_count; ++i) {
        printf("  - %s: %d\n", generi[i].genere, generi[i].count);
    }
}
