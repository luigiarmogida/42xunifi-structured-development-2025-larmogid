#include "expense.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

size_t	ft_strlen(char *s) {
	size_t	i = 0;
	if (!s) return 0;
	while (s[i]) i++;
	return i;
}

char	*ft_strdup(const char *s1) {
	size_t	len = ft_strlen((char *)s1);
	char	*copy = malloc(len + 1);
	if (!copy) return NULL;
	for (size_t i = 0; i <= len; i++)
		copy[i] = s1[i];
	return copy;
}

char	*ft_strchr(char *s, int c) {
	int	i = 0;
	if (!s) return 0;
	if (c == '\0') return (char *)&s[ft_strlen(s)];
	while (s[i])
		if (s[i++] == (char)c) return (char *)&s[i - 1];
	return 0;
}

char	*ft_strjoin(char *s1, char *s2) {
	if (!s1) {
		s1 = malloc(1);
		if (!s1) return NULL;
		s1[0] = '\0';
	}
	if (!s1 || !s2) return NULL;

	size_t	len1 = ft_strlen(s1);
	size_t	len2 = ft_strlen(s2);
	char	*result = malloc(len1 + len2 + 1);
	if (!result) return NULL;

	for (size_t i = 0; i < len1; i++) result[i] = s1[i];
	for (size_t i = 0; i < len2; i++) result[len1 + i] = s2[i];
	result[len1 + len2] = '\0';

	free(s1);
	return result;
}

// Funzioni per l'expense tracker

char *trim_whitespace(char *str) {
	if (!str) return NULL;
	while (isspace((unsigned char)*str)) str++;
	if (*str == '\0') return str;
	char *end = str + ft_strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;
	*(end + 1) = '\0';
	return str;
}

char *to_lowercase(const char *str) {
	if (!str) return NULL;
	size_t len = ft_strlen((char *)str);
	char *lower = malloc(len + 1);
	if (!lower) return NULL;
	for (size_t i = 0; i < len; i++)
		lower[i] = tolower((unsigned char)str[i]);
	lower[len] = '\0';
	return lower;
}

int is_valid_date_format(const char *date) {
    if (!date || strlen(date) != 10)
        return 0;
    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && date[i] != '-')
            return 0;
        if (i != 4 && i != 7 && !isdigit((unsigned char)date[i]))
            return 0;
    }
    return 1;
}

int compare_dates(const char *d1, const char *d2) {
    return strcmp(d1, d2);
}

void print_warning(const char *msg) {
    fprintf(stderr, "[Warning] %s\n", msg);
}