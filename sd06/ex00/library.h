#ifndef LIBRARY_H
#define LIBRARY_H

#include <stddef.h>  // per size_t

typedef struct {
    char *titolo;
    char *autore;
    char *genere;
    int anno_pubblicazione;
    int numero_pagine;
} Libro;

typedef struct {
    Libro *libri;
    size_t count;      // numero di libri attualmente presenti
    size_t capacity;   // capacità allocata
} CatalogoLibri;

// Caricamento da file CSV
int load_catalog(const char *filename, CatalogoLibri *catalogo);

void strip_newline(char *s);

// Visualizzazione e ricerca
void print_all_books(const CatalogoLibri *catalogo);
void search_by_title(const CatalogoLibri *catalogo, const char *titolo);
void search_by_author(const CatalogoLibri *catalogo, const char *autore);
// void search_by_genre(...) è da commentare o implementare

// Statistiche
void print_statistics(const CatalogoLibri *catalogo);

// Ordinamenti (da implementare o commentare)
/// void sort_by_title(CatalogoLibri *catalogo);
/// void sort_by_year(CatalogoLibri *catalogo);

// Pulizia memoria
void free_catalog(CatalogoLibri *catalogo);

#endif
