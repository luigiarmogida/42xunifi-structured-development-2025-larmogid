#ifndef CONTACT_H
# define CONTACT_H

typedef struct s_contact {
    int  id;            // identificativo univoco
    char *name;
    char *email;
    char *phone;
    char *address;
    char *city;
    char *zip;

    // Nuovi campi bonus (ex05)
    char *group;        // può essere NULL
    char *birthdate;    // formato "YYYY-MM-DD", può essere NULL
} t_contact;

// CRUD
t_contact *parse_contact(char *line);
int        validate_contact(t_contact *c);
void       free_contact(t_contact *c);
void       print_contact(const t_contact *contact);

#endif
