#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io_handler.h"

// 🧪 Verifica che l'ID non sia già presente nella lista
static int is_duplicate_id(t_contact_list *list, int id)
{
	for (int i = 0; i < list->size; i++)
	{
		if (list->array[i]->id == id)
			return 1;
	}
	return 0;
}

// 📥 Carica i contatti dal file CSV
int load_contacts(const char *filename, t_contact_list *list)
{
	FILE *fp = fopen(filename, "r");
	char *line = NULL;
	size_t len = 0;
	int read_len;
	int count = 0, skipped = 0;

	if (!fp)
	{
		fprintf(stderr, "Error: cannot open file '%s'\n", filename);
		return 0;
	}

	while ((read_len = getline(&line, &len, fp)) != -1)
	{
		// rimuove newline finale se presente
		if (read_len > 0 && line[read_len - 1] == '\n')
			line[--read_len] = '\0';

		char *copy = strdup(line); // strtok modifica la stringa
		t_contact *c = parse_contact(copy);
		if (!c || !validate_contact(c) || is_duplicate_id(list, c->id))
		{
			fprintf(stderr, "Skipping invalid line: %s\n", line);
			free_contact(c);
			free(copy);
			skipped++;
			continue;
		}
		add_contact(list, c);
		free(copy);
		count++;
	}
	free(line);
	fclose(fp);

	printf("Loaded %d contact(s), skipped %d invalid line(s).\n", count, skipped);
	return 1;
}

// 📤 Salva i contatti in un file temporaneo, poi rinomina
int save_contacts(const char *filename, t_contact_list *list)
{
	char tmp_filename[1024];
	snprintf(tmp_filename, sizeof(tmp_filename), "%s.tmp", filename);

	FILE *fp = fopen(tmp_filename, "w");
	if (!fp)
	{
		fprintf(stderr, "Error: cannot write to '%s'\n", tmp_filename);
		return 0;
	}

	for (int i = 0; i < list->size; i++)
	{
		t_contact *c = list->array[i];
		fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%s\n",
			c->id,
			c->name,
			c->phone,
			c->email,
			c->city,
			c->address,
			c->group ? c->group : "",
			c->birthdate ? c->birthdate : "");
	}

	fclose(fp);

	// Rinominazione atomica
	if (rename(tmp_filename, filename) != 0)
	{
		fprintf(stderr, "Error: failed to rename temp file to '%s'\n", filename);
		return 0;
	}

	printf("Contacts saved to '%s'.\n", filename);
	return 1;
}
