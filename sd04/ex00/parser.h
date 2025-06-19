#ifndef PARSER_H
#define PARSER_H

#include "book.h"

/*
** Analizza una singola riga del file e tenta di estrarre i campi ID, titolo e autore.
** Restituisce 0 in caso di successo, -1 se la riga è malformata.
*/
int parse_line(const char *line, Book *book);

#endif // PARSER_H
