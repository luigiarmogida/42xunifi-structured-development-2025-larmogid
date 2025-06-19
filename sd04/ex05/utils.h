#ifndef UTILS_H
# define UTILS_H

char    *strdup_safe(const char *s);
int      is_valid_email(const char *s);
int      is_valid_phone(const char *s);
int      is_valid_date(const char *s); // YYYY-MM-DD
int      date_within_next_month(const char *birthdate);

#endif
