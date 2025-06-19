#include "book.h"

// parsing.c
int     load_catalog(const char *filename, Library *lib);
int     parse_line(const char *line, Book *book);

// search.c
void    search_by_title(const Library *lib, const char *query);
void    search_by_author(const Library *lib, const char *query);

// utils.c
char    *trim_whitespace(char *str);
int     strcasestr_in(const char *haystack, const char *needle);

// io.c
void    print_book(const Book *book);
void    prompt_search_mode(int *mode);
void    prompt_search_query(char *buffer, size_t size);
