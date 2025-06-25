#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include "contact_list.h"

#define INITIAL_CAPACITY 32

// Crea una nuova lista di contatti
t_contact_list *create_contact_list(void)
{
	t_contact_list *list = malloc(sizeof(t_contact_list));
	if (!list)
		return NULL;
	list->array = malloc(sizeof(t_contact *) * INITIAL_CAPACITY);
	if (!list->array)
	{
		free(list);
		return NULL;
	}
	list->size = 0;
	list->capacity = INITIAL_CAPACITY;
	list->max_id = 0;
	return list;
}

// Libera l'intera lista e i contatti associati
void free_contact_list(t_contact_list *list)
{
	int i;

	if (!list)
		return;
	for (i = 0; i < list->size; i++)
		free_contact(list->array[i]);
	free(list->array);
	free(list);
}

// Espande la capacità interna della lista
static int grow_list(t_contact_list *list)
{
	int new_capacity = list->capacity * 2;
	t_contact **new_array = malloc(sizeof(t_contact *) * new_capacity);
	if (!new_array)
		return 0;
	for (int i = 0; i < list->size; i++)
		new_array[i] = list->array[i];
	free(list->array);
	list->array = new_array;
	list->capacity = new_capacity;
	return 1;
}

// Aggiunge un nuovo contatto alla lista (verifica duplicati a monte)
int add_contact(t_contact_list *list, t_contact *new_contact)
{
	if (!list || !new_contact)
		return 0;
	if (list->size == list->capacity && !grow_list(list))
		return 0;
	list->array[list->size++] = new_contact;
	if (new_contact->id > list->max_id)
		list->max_id = new_contact->id;
	return 1;
}

// Elimina un contatto per ID (spostando gli elementi successivi)
int delete_contact(t_contact_list *list, int id)
{
	for (int i = 0; i < list->size; i++)
	{
		if (list->array[i]->id == id)
		{
			free_contact(list->array[i]);
			for (int j = i; j < list->size - 1; j++)
				list->array[j] = list->array[j + 1];
			list->size--;
			return 1;
		}
	}
	return 0;
}

// Trova un contatto per ID (restituisce NULL se non trovato)
t_contact *find_contact_by_id(t_contact_list *list, int id)
{
	for (int i = 0; i < list->size; i++)
	{
		if (list->array[i]->id == id)
			return list->array[i];
	}
	return NULL;
}

// Stampa tutti i contatti
void list_all_contacts(t_contact_list *list)
{
	for (int i = 0; i < list->size; i++)
	{
		t_contact *c = list->array[i];
		printf("[%d] %s | %s | %s | %s | %s\n",
			c->id, c->name, c->phone, c->email, c->city, c->address);
	}
}

// Ricerca per sottostringa nel nome o nella città
void search_contacts(t_contact_list *list, const char *substr, int by_city)
{
	for (int i = 0; i < list->size; i++)
	{
		const char *field = by_city ? list->array[i]->city : list->array[i]->name;
		if (strstr(field, substr)) // semplice match case-sensitive
		{
			t_contact *c = list->array[i];
			printf("[%d] %s | %s | %s | %s | %s\n",
				c->id, c->name, c->phone, c->email, c->city, c->address);
		}
	}
}
