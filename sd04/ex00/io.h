#ifndef IO_H
#define IO_H

#include "book.h"

/*
** Stampa le informazioni di un singolo libro.
*/
void print_book(const Book *book);

/*
** Richiede all'utente di scegliere la modalità di ricerca.
** Restituisce 1 per titolo, 2 per autore.
*/
int prompt_search_mode(void);

/*
** Richiede la query di ricerca.
** Riempie il buffer passato con l'input dell'utente.
*/
void prompt_search_query(char *buffer, size_t size);

#endif // IO_H
