#ifndef GROUPS_H
# define GROUPS_H

# include "contact_list.h"

void assign_group(t_contact *c, const char *group);
void list_contacts_by_group(t_contact_list *list, const char *group);

#endif
