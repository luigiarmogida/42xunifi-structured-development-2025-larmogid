#ifndef IO_HANDLER_H
# define IO_HANDLER_H

# include "contact_list.h"

int		load_contacts(const char *filename, t_contact_list *list);
int		save_contacts(const char *filename, t_contact_list *list);

#endif
