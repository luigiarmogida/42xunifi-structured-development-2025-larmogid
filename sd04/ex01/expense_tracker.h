#ifndef EXPENSE_TRACKER_H
# define EXPENSE_TRACKER_H

# include <stdbool.h>

/*
** Definisce il numero massimo di record che possiamo caricare in memoria.
*/
# define MAX_RECORDS 1000

/*
** Rappresenta una data nel formato YYYY-MM-DD come tre interi separati.
*/
typedef struct s_date {
    int year;
    int month;
    int day;
}   t_date;

/*
** Struttura che rappresenta una singola spesa.
*/
typedef struct s_expense {
    t_date      date;
    float       amount;
    char        *category;
    char        *description;
}   t_expense;

/*
** Riepilogo statistico per un insieme di spese.
*/
typedef struct s_summary {
    int     count;
    float   total;
    float   average;
}   t_summary;

/*
** Statistiche per categoria: spesa totale e percentuale.
*/
typedef struct s_category_stat {
    char    *name;
    float   total;
    float   percentage;
}   t_category_stat;

#endif
