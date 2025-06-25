#ifndef EXPENSE_H
#define EXPENSE_H

#define MAX_EXPENSES 1000 // massimo numero di spese da caricare in memoria

#include <stddef.h>  // per size_t

typedef struct s_expense {
    char date[11];        // "YYYY-MM-DD"
    float amount;         // > 0
    char *category;       // allocata dinamicamente, trim/casefold
    char *description;    // allocata dinamicamente, trim
} t_expense;

typedef struct s_expense_list {
    t_expense expenses[MAX_EXPENSES];
    int count;
} t_expense_list;

typedef enum e_filter_type {
    FILTER_ALL,
    FILTER_CATEGORY,
    FILTER_DATES
} t_filter_type;

typedef struct s_filter {
    t_filter_type type;
    char *category;      // se type == FILTER_CATEGORY
    char start_date[11]; // se type == FILTER_DATES
    char end_date[11];
} t_filter;

typedef struct s_category_summary {
    char *category;
    float total;
    float percentage;
} t_category_summary;

typedef struct s_summary {
    int record_count;
    float total_amount;
    float average;
    t_category_summary *categories;
    int category_count;
} t_summary;

// --- Funzioni di parsing e validazione ---

int     load_expenses_from_file(const char *filename, t_expense_list *list);
int     is_valid_line(const char *line);
int     parse_line(const char *line, t_expense *exp);  // restituisce 1 se valida

// --- Funzioni di pulizia e normalizzazione ---

char    *trim_whitespace(char *str);
char    *to_lowercase(const char *str);
int     is_valid_date_format(const char *date);
int     compare_dates(const char *d1, const char *d2); // restituisce -1, 0, 1

// --- Interazione con l’utente ---

void    prompt_filter(t_filter *filter);

// --- Filtro delle spese ---

void    filter_expenses(const t_expense_list *input, const t_filter *filter, t_expense_list *output);

// --- Analisi delle spese ---

void    compute_summary(const t_expense_list *list, t_summary *summary);
void    free_summary(t_summary *summary);

// --- Output finale ---

void    print_summary(const t_summary *summary);
void    print_warning(const char *msg);

// --- Cleanup memoria ---

void    free_expense(t_expense *exp);
void    free_expense_list(t_expense_list *list);

#endif