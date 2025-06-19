#ifndef SUMMARY_H
# define SUMMARY_H

# include "expense_tracker.h"

/*
** Calcola le statistiche generali (conteggio, totale, media).
*/
void    compute_summary(t_expense *records[], int size, t_summary *summary);

/*
** Calcola la suddivisione per categoria.
*/
void    compute_category_breakdown(t_expense *records[], int size, t_category_stat stats[], int *count);

/*
** Stampa un riepilogo completo.
*/
void    print_summary(t_summary *summary, t_category_stat stats[], int stat_count);

#endif
