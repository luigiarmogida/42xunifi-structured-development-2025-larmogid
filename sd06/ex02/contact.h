#ifndef CONTACT_H
# define CONTACT_H

typedef struct s_contact {
	int     id;
	char    *name;
	char    *phone;
	char    *email;
	char    *city;
	char    *address;
}	t_contact;

t_contact	*parse_contact(char *line);
int			validate_contact(t_contact *c);
void		free_contact(t_contact *c);

#endif
