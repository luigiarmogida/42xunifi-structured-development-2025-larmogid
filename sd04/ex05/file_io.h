#ifndef FILE_IO_H
# define FILE_IO_H

#include "contact.h"

# define MAX_LINE_LEN 1024
# define FIELD_COUNT_ORIGINAL 6
# define FIELD_COUNT_EXTENDED 8

t_contact   **load_contacts(const char *filename, int *count);
int          save_contacts(const char *filename, t_contact **contacts, int count);

#endif
