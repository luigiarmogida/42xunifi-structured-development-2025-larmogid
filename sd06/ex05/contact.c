#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

void print_contact(const t_contact *c) {
    if (!c) return;
    printf("Name: %s\nEmail: %s\nPhone: %s\n",
        c->name ? c->name : "-", c->email ? c->email : "-", c->phone ? c->phone : "-");
    printf("Address: %s, %s %s\n",
        c->address ? c->address : "-", c->city ? c->city : "-", c->zip ? c->zip : "-");
    if (c->group)
        printf("Group: %s\n", c->group);
    if (c->birthdate)
        printf("Birthday: %s\n", c->birthdate);
}

// 🔧 Trim spazi iniziali/finali
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

// 📅 Validazione data di nascita (formato YYYY-MM-DD semplice)
static int is_valid_birthdate(const char *date)
{
	if (!date || strlen(date) != 10)
		return 0;
	if (date[4] != '-' || date[7] != '-')
		return 0;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return 0;
	}
	return 1;
}

// 📦 Libera memoria del contatto (esteso)
void free_contact(t_contact *c)
{
	if (!c) return;
	free(c->name);
	free(c->phone);
	free(c->email);
	free(c->city);
	free(c->address);
	free(c->group);
	free(c->birthdate);
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
	if (c->birthdate && !is_valid_birthdate(c->birthdate))
		return 0;
	return 1;
}

// 🧩 Parsing riga CSV → struttura Contact (fallback compatibile)
t_contact *parse_contact(char *line)
{
	t_contact *c = malloc(sizeof(t_contact));
	if (!c)
		return NULL;

	char *fields[8];
	int i = 0;
	char *token = strtok(line, ",");

	while (token && i < 8)
		fields[i++] = token, token = strtok(NULL, ",");

	if (i < 6)
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

	// Campi opzionali (fallback se assenti)
	c->group = (i > 6) ? trim_whitespace(fields[6]) : NULL;
	c->birthdate = (i > 7) ? trim_whitespace(fields[7]) : NULL;

	return c;
}
