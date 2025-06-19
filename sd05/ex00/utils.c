#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

// Copia una stringa (come strdup, ma scritta a mano)
char *string_duplicate(const char *s)
{
	size_t len = 0;
	char *copy;

	if (!s)
		return (NULL);
	while (s[len])
		len++;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		copy[i] = s[i];
	copy[len] = '\0';
	return copy;
}

// Converte una stringa a float (usa atof dalla stdlib)
float string_to_float(const char *s)
{
	return (float)atof(s);
}

// Divide una stringa in base a un separatore (come split)
char **string_split(const char *str, char sep)
{
	char	**result;
	size_t	count = 1;
	size_t	i = 0, start = 0, word = 0;

	if (!str)
		return (NULL);

	// Conta i separatori
	while (str[i])
		if (str[i++] == sep)
			count++;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);

	i = 0;
	while (str[i])
	{
		if (str[i] == sep || str[i + 1] == '\0')
		{
			size_t end = (str[i] == sep) ? i : i + 1;
			size_t len = end - start;
			result[word] = malloc(len + 1);
			if (!result[word])
				return (free_split(result), NULL);
			for (size_t j = 0; j < len; j++)
				result[word][j] = str[start + j];
			result[word][len] = '\0';
			word++;
			start = i + 1;
		}
		i++;
	}
	result[word] = NULL;
	return result;
}

// Libera un array creato da string_split
void free_split(char **arr)
{
	size_t i = 0;

	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
