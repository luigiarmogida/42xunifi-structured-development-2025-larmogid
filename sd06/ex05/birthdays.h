#ifndef BIRTHDAYS_H
# define BIRTHDAYS_H

# include "contact_list.h"

int  is_upcoming_birthday(const char *birthdate);
void show_upcoming_birthdays(t_contact_list *list);

#endif
