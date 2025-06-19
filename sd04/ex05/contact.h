#ifndef CONTACT_H
# define CONTACT_H

typedef struct s_contact
{
    int     id;
    char    *first_name;
    char    *last_name;
    char    *email;
    char    *phone;
    char    *address;
    char    *group;        // optional
    char    *birthdate;    // format: YYYY-MM-DD (optional)
}   t_contact;

t_contact   *create_contact(char **fields);
void        free_contact(t_contact *c);
void        print_contact(const t_contact *c);
int         edit_contact(t_contact *c);
int         validate_contact(const t_contact *c);

#endif
