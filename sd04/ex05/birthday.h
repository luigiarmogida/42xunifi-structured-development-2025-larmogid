#ifndef BIRTHDAY_H
# define BIRTHDAY_H

#include "contact.h"

int  is_upcoming_birthday(const char *birthdate);
void print_upcoming_birthdays(t_contact **contacts, int count);

#endif
