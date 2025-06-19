#ifndef FILTER_H
# define FILTER_H

# include "expense_tracker.h"

/*
** Filtra i record per nome categoria (case-insensitive, parziale).
*/
int     filter_by_category(t_expense *src[], t_expense *dst[], int size, const char *category);

/*
** Filtra i record per un intervallo di date incluso.
*/
int     filter_by_date_range(t_expense *src[], t_expense *dst[], int size, t_date start, t_date end);

/*
** Copia tutti i record da src[] a dst[].
*/
int     filter_all(t_expense *src[], t_expense *dst[], int size);

#endif
