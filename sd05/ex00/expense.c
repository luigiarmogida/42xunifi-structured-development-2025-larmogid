#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>    // per close()
#include <stdio.h>     // per printf (o ft_printf)
#include "expense.h"
#include "get_next_line.h"
#include <string.h>
#include "utils.h"     // string_duplicate, string_split, string_to_float, free_split
// Crea un nuovo nodo di spesa
static t_expense *create_expense(char *date, char *category, float amount, char *description)
{
	t_expense *new;

	new = malloc(sizeof(t_expense));
	if (!new)
		return (NULL);
	new->date = string_duplicate(date);
	new->category = string_duplicate(category);
	new->description = string_duplicate(description);
	new->amount = amount;
	new->next = NULL;
	return (new);
}

// Inserisce un nodo in fondo alla lista
static void append_expense(t_expense **head, t_expense *new_node)
{
	t_expense *curr;

	if (!head || !new_node)
		return;
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}

// Converte una riga CSV in un nodo spesa
static t_expense *parse_line_to_expense(char *line)
{
	char	**fields;
	t_expense *expense;

	fields = string_split(line, ',');
	if (!fields)
		return (NULL);
	if (!fields[0] || !fields[1] || !fields[2] || !fields[3])
	{
		free_split(fields);
		return (NULL);
	}
	expense = create_expense(fields[0], fields[1], string_to_float(fields[2]), fields[3]);
	free_split(fields);
	return (expense);
}

// Carica le spese da un file CSV
t_expense *load_expenses(const char *filename)
{
	t_expense *head = NULL;
	t_expense *new_expense;
	char *line;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		new_expense = parse_line_to_expense(line);
		if (new_expense)
			append_expense(&head, new_expense);
		free(line);
	}
	close(fd);
	return (head);
}

// Stampa la lista delle spese
void print_expenses(const t_expense *head)
{
	printf("%-12s | %-10s | %8s | %s\n", "Date", "Category", "Amount", "Description");
	printf("---------------------------------------------------------------\n");
	while (head)
	{
		printf("%-12s | %-10s | %7.2f € | %s\n",
			head->date,
			head->category,
			head->amount,
			head->description);
		head = head->next;
	}
}

// Calcola il totale
float total_expenses(const t_expense *head)
{
	float sum = 0.0f;

	while (head)
	{
		sum += head->amount;
		head = head->next;
	}
	return (sum);
}

// Libera la memoria
void free_expenses(t_expense *head)
{
	t_expense *tmp;

	while (head)
	{
		tmp = head->next;
		free(head->date);
		free(head->category);
		free(head->description);
		free(head);
		head = tmp;
	}
}