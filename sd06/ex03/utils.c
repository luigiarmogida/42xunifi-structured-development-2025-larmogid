#include "movie.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// trimming e date

char *trim_whitespace(char *str) {
	if (!str)
		return NULL;
	while (isspace((unsigned char)*str)) str++;
	if (*str == 0) return str;

	char *end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;
	end[1] = '\0';
	return str;
}

int is_valid_date(const char *date) {
	if (strlen(date) != 10)
		return 0;
	if (date[4] != '-' || date[7] != '-')
		return 0;
	for (int i = 0; i < 10; ++i) {
		if (i == 4 || i == 7) continue;
		if (!isdigit(date[i])) return 0;
	}
	// possiamo aggiungere controlli più avanzati se serve
	return 1;
}

int is_duplicate_id(t_movie_list *list, int id) {
	t_movie *cur = list->head;
	while (cur) {
		if (cur->id == id)
			return 1;
		cur = cur->next;
	}
	return 0;
}
