#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui_menu.h"
#include "contact_list.h"
#include "contact.h"
#include "io_handler.h"
#include "groups.h"
#include "birthdays.h"

// 🔁 Legge una riga da input
static char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	int read_len = getline(&line, &len, stdin);
	if (read_len == -1)
	{
		free(line);
		return NULL;
	}
	// Rimuove newline
	if (line[read_len - 1] == '\n')
		line[read_len - 1] = '\0';
	return line;
}

// 🔍 Richiede una sottostringa per la ricerca
static void handle_search(t_contact_list *list, int by_city)
{
	printf("Enter substring to search: ");
	char *substr = read_line();
	if (!substr)
		return;
	search_contacts(list, substr, by_city);
	free(substr);
}

// ➕ Aggiunge un contatto da input interattivo
static void handle_add(t_contact_list *list)
{
	t_contact *c = malloc(sizeof(t_contact));
	if (!c)
		return;

	c->id = list->max_id + 1; // ID univoco automatico

	printf("Name: ");     c->name = read_line();
	printf("Phone: ");    c->phone = read_line();
	printf("Email: ");    c->email = read_line();
	printf("City: ");     c->city = read_line();
	printf("Address: ");  c->address = read_line();
	printf("Group (optional): ");    c->group = read_line();
	printf("Birthdate (YYYY-MM-DD, optional): "); c->birthdate = read_line();

	if (!validate_contact(c))
	{
		printf("Invalid contact. Try again.\n");
		free_contact(c);
		return;
	}
	add_contact(list, c);
	printf("Contact added with ID %d.\n", c->id);
}

// ✏️ Modifica contatto esistente
static void handle_update(t_contact_list *list)
{
	printf("Enter ID to update: ");
	char *line = read_line();
	if (!line) return;
	int id = atoi(line);
	free(line);

	t_contact *c = find_contact_by_id(list, id);
	if (!c)
	{
		printf("Contact not found.\n");
		return;
	}

	printf("New name (blank to skip): ");
	char *input = read_line();
	if (input && strlen(input)) {
		free(c->name);
		c->name = input;
	} else free(input);

	printf("New phone: ");
	input = read_line();
	if (input && strlen(input)) {
		free(c->phone);
		c->phone = input;
	} else free(input);

	printf("New email: ");
	input = read_line();
	if (input && strlen(input)) {
		free(c->email);
		c->email = input;
	} else free(input);

	printf("New city: ");
	input = read_line();
	if (input && strlen(input)) {
		free(c->city);
		c->city = input;
	} else free(input);

	printf("New address: ");
	input = read_line();
	if (input && strlen(input)) {
		free(c->address);
		c->address = input;
	} else free(input);

	printf("New group: ");
	input = read_line();
	if (input && strlen(input)) {
		free(c->group);
		c->group = input;
	} else free(input);

	printf("New birthdate: ");
	input = read_line();
	if (input && strlen(input)) {
		free(c->birthdate);
		c->birthdate = input;
	} else free(input);

	if (!validate_contact(c))
		printf("Warning: updated contact is now invalid.\n");
	else
		printf("Contact updated.\n");
}

// ❌ Elimina contatto
static void handle_delete(t_contact_list *list)
{
	printf("Enter ID to delete: ");
	char *line = read_line();
	if (!line) return;
	int id = atoi(line);
	free(line);

	if (delete_contact(list, id))
		printf("Contact deleted.\n");
	else
		printf("Contact not found.\n");
}

static void handle_list_by_group(t_contact_list *list)
{
	printf("Enter group name to filter: ");
	char *group = read_line();
	if (!group)
		return;
	list_contacts_by_group(list, group);
	free(group);
}

static void handle_birthdays(t_contact_list *list)
{
	show_upcoming_birthdays(list);
}

void run_menu(t_contact_list *list, const char *filename)
{
	int running = 1;

	while (running)
	{
		printf("\n=== Contact Manager ===\n\n");
		printf("1. List all contacts\n");
		printf("2. Search by name\n");
		printf("3. Search by city\n");
		printf("4. Add new contact\n");
		printf("5. Update contact\n");
		printf("6. Delete contact\n");
		printf("7. List contacts by group\n");
		printf("8. Show upcoming birthdays\n");
		printf("9. Save and exit\n");

		printf("\n> ");

		char *choice = read_line();
		if (!choice) continue;

		switch (atoi(choice))
		{
			case 1: list_all_contacts(list); break;
			case 2: handle_search(list, 0); break;
			case 3: handle_search(list, 1); break;
			case 4: handle_add(list); break;
			case 5: handle_update(list); break;
			case 6: handle_delete(list); break;
			case 7: handle_list_by_group(list); break;
			case 8: handle_birthdays(list); break;
			case 9:
				if (save_contacts(filename, list))
					running = 0;
				break;
			default: printf("Invalid choice.\n"); break;
		}
		free(choice);
	}
}