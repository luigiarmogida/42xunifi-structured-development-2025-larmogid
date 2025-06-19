#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>  // per size_t, malloc, free
# include <string.h>  // per strlen, atof (in string_to_float)
# include <ctype.h>   // se ti servirà per validazioni future

// Duplica una stringa (equivalente di strdup)
char	*string_duplicate(const char *s);

// Converte una stringa in float (wrapper su atof)
float	string_to_float(const char *s);

// Divide una stringa in base a un separatore (come ft_split)
char	**string_split(const char *str, char sep);

// Libera un array di stringhe allocato con string_split
void	free_split(char **arr);

#endif
