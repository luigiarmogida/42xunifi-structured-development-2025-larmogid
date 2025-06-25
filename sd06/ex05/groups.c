#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "groups.h"

void assign_group(t_contact *c, const char *group)
{
    if (!c) return;
    free(c->group);
    c->group = strdup(group);
}

void list_contacts_by_group(t_contact_list *list, const char *group)
{
    printf("Contacts in group '%s':\n", group);
    for (int i = 0; i < list->size; i++)
    {
        t_contact *c = list->array[i];
        if (c->group && strcmp(c->group, group) == 0)
        {
            printf("[%d] %s | %s | %s\n", c->id, c->name, c->email, c->phone);
        }
    }
}
