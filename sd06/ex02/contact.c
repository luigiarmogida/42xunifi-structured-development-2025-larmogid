#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// 🔧 Funzione di utilità: trim degli spazi iniziali e finali
static char *trim_whitespace(char *str)
{
	char *end;

	while (isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return strdup(""); // stringa vuota

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;
	end[1] = '\0';

	return strdup(str);
}

// 🔍 Validazione email: una sola '@', con dominio e almeno un '.' dopo
static int is_valid_email(const char *email)
{
	const char *at = strchr(email, '@');
	if (!at || at == email || *(at + 1) == '\0')
		return 0;
	if (!strchr(at + 1, '.'))
		return 0;
	return 1;
}

// ☎️ Validazione telefono: almeno un numero
static int is_valid_phone(const char *phone)
{
	while (*phone)
	{
		if (isdigit((unsigned char)*phone))
			return 1;
		phone++;
	}
	return 0;
}

// 📦 Libera memoria del contatto
void free_contact(t_contact *c)
{
	if (!c)
		return;
	free(c->name);
	free(c->phone);
	free(c->email);
	free(c->city);
	free(c->address);
	free(c);
}

// 🧪 Valida un contatto già parsato (controlli logici, non duplicati!)
int validate_contact(t_contact *c)
{
	if (!c || c->id <= 0)
		return 0;
	if (!c->name || strlen(c->name) == 0)
		return 0;
	if (!c->city || strlen(c->city) == 0)
		return 0;
	if (!c->phone || !is_valid_phone(c->phone))
		return 0;
	if (!c->email || !is_valid_email(c->email))
		return 0;
	return 1;
}

// 🧩 Parsing riga CSV → struttura Contact
t_contact *parse_contact(char *line)
{
	t_contact *c = malloc(sizeof(t_contact));
	if (!c)
		return NULL;

	char *fields[6];
	int i = 0;
	char *token = strtok(line, ",");

	while (token && i < 6)
		fields[i++] = token, token = strtok(NULL, ",");

	if (i != 6)
	{
		free(c);
		return NULL;
	}

	c->id = atoi(fields[0]);
	c->name = trim_whitespace(fields[1]);
	c->phone = trim_whitespace(fields[2]);
	c->email = trim_whitespace(fields[3]);
	c->city = trim_whitespace(fields[4]);
	c->address = trim_whitespace(fields[5]);

	return c;
}
