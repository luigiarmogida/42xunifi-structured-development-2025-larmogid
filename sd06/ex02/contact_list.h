
#ifndef CONTACT_LIST_H
# define CONTACT_LIST_H

# include "contact.h"

//Gestisce la lista dinamica di contatti.

typedef struct s_contact_list {
	t_contact	**array;
	int			size;
	int			capacity;
	int			max_id;
}	t_contact_list;

t_contact_list	*create_contact_list(void);
void			free_contact_list(t_contact_list *list);
int				add_contact(t_contact_list *list, t_contact *new_contact);
int				delete_contact(t_contact_list *list, int id);
t_contact		*find_contact_by_id(t_contact_list *list, int id);
void			search_contacts(t_contact_list *list, const char *substr, int by_city);
void			list_all_contacts(t_contact_list *list);

#endif
