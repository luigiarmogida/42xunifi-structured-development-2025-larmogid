#ifndef SEARCH_H
#define SEARCH_H

#include "book.h"

/*
** Cerca i libri il cui titolo contiene la stringa query.
*/
void search_by_title(const Library *lib, const char *query);

/*
** Cerca i libri il cui autore contiene la stringa query.
*/
void search_by_author(const Library *lib, const char *query);

#endif // SEARCH_H
