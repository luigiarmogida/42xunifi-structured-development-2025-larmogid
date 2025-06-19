#ifndef BOOK_H
#define BOOK_H

#include <stddef.h>  // Per size_t

// Dimensione massima dei campi titolo e autore.
// Questi limiti sono scelti per semplicità e stabilità in ambiente console.
#define MAX_FIELD_LEN 128

// Numero massimo di libri gestibili in memoria.
// Secondo specifica, il catalogo non supererà 1000 voci.
#define MAX_BOOKS 1000

// ---------------------------
// Struttura dati principali
// ---------------------------

/*
** Rappresenta un singolo libro del catalogo.
** I campi di ogni libro sono ricavati da una riga del file CSV, 
** in formato: ID numerico, Titolo, Autore.
** Questi dati provengono da una singola riga del file di catalogo.
*/
typedef struct s_book {
    int     id;                             // Identificativo numerico univoco del libro
    char    title[MAX_FIELD_LEN];           // Titolo del libro (stringa null-terminated)
    char    author[MAX_FIELD_LEN];          // Nome dell'autore (stringa null-terminated)
}   Book;

/*
** Struttura contenitore per tutta la libreria caricata in memoria.
** Tiene traccia dei libri letti correttamente e del loro numero attuale.
*/
typedef struct s_library {
    Book    books[MAX_BOOKS];               // Array di libri caricati
    int     count;                          // Numero effettivo di libri validi letti
}   Library;

// ---------------------------
// Prototipi delle funzioni
// ---------------------------

/*
** Carica il catalogo dal file indicato.
** Ogni riga del file viene analizzata; le righe malformate vengono ignorate.
** Ogni riga valida viene convertita in una struttura Book e salvata in 'lib'.
** - filename: percorso del file di catalogo
** - lib: puntatore a una struttura Library da riempire
** Ritorna:
** - numero di libri caricati con successo
** - -1 se il file non può essere aperto
*/
int     load_catalog(const char *filename, Library *lib);

/*
** Cerca libri il cui titolo contiene la sottostringa 'query' (case-insensitive).
** - lib: puntatore alla libreria
** - query: stringa da cercare nel titolo
** Stampa i risultati trovati in formato leggibile.
*/
void    search_by_title(const Library *lib, const char *query);

/*
** Cerca libri il cui autore contiene la sottostringa 'query' (case-insensitive).
** - lib: puntatore alla libreria
** - query: stringa da cercare nel nome dell'autore
** Stampa i risultati trovati in formato leggibile.
*/
void    search_by_author(const Library *lib, const char *query);

/*
** Rimuove eventuali spazi iniziali e finali da una stringa.
** La modifica è in-place e la stringa risultante è null-terminated.
** - str: stringa da ripulire
** Ritorna: puntatore alla stringa ripulita.
*/
char    *trim_whitespace(char *str);

/*
** Stampa le informazioni di un singolo libro in formato leggibile.
** - book: puntatore al libro da stampare
*/
void    print_book(const Book *book);

#endif // BOOK_H
