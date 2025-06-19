#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

# include <stdlib.h>

# define MAX_CONTACTS 1000
# define FIELD_LEN 128
# define ADDRESS_LEN 256

typedef struct s_contact {
	int     id;
	char    name[FIELD_LEN];
	char    phone[FIELD_LEN];
	char    email[FIELD_LEN];
	char    city[FIELD_LEN];
	char    address[ADDRESS_LEN];
}   t_contact;

typedef struct s_contact_list {
	t_contact   contacts[MAX_CONTACTS];
	int         count;
	int         max_id;
}   t_contact_list;

// load.c
int     load_contacts(const char *filename, t_contact_list *list);
int     validate_and_add_contact(char *line, t_contact_list *list);

// menu.c
void    menu_loop(t_contact_list *list, const char *filename);

// operations.c
void    list_contacts(t_contact_list *list);
void    search_by_name(t_contact_list *list, const char *query);
void    search_by_city(t_contact_list *list, const char *query);
int     add_contact(t_contact_list *list);
int     update_contact(t_contact_list *list, int id);
int     delete_contact(t_contact_list *list, int id);
int     save_contacts(const char *filename, t_contact_list *list);

// utils.c
char    *trim(char *str);
int     is_valid_phone(const char *phone);
int     is_valid_email(const char *email);
int     is_positive_int(const char *str);

#endif
