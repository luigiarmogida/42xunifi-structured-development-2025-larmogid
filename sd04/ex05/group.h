#ifndef GROUP_H
# define GROUP_H

#include "contact.h"

char    **get_all_groups(t_contact **contacts, int count);
void     print_contacts_by_group(t_contact **contacts, int count, const char *group);
int      assign_group(t_contact *c, const char *group);

#endif
