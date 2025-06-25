#include "contact.h"
#include <stdlib.h>
#include <string.h>

#define MAX_FIELDS 8

t_contact *create_contact_from_fields(char **fields, int field_count) {
    t_contact *c = malloc(sizeof(t_contact));
    if (!c) return NULL;

    c->name = strdup(fields[0]);
    c->email = strdup(fields[1]);
    c->phone = strdup(fields[2]);
    c->address = strdup(fields[3]);
    c->city = strdup(fields[4]);
    c->zip = strdup(fields[5]);

    c->group = (field_count > 6) ? strdup(fields[6]) : NULL;
    c->birthdate = (field_count > 7) ? strdup(fields[7]) : NULL;

    return c;
}
