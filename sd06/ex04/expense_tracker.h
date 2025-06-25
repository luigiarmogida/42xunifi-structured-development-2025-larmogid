#ifndef EXPENSE_TRACKER_H
# define EXPENSE_TRACKER_H

# include <stdlib.h>  // malloc, free
# include <stdio.h>   // FILE, fopen, fclose, etc.
# include <string.h>  // strcmp, strdup, etc.
# include <stdbool.h> // bool, true, false

# define MAX_EXPENSES 1000
# define MAX_LINE_LEN 512

typedef struct s_expense {
	int     id;
	char   *date;        // formato "YYYY-MM-DD"
	float   amount;
	char   *category;
	char   *description; // opzionale
}   Expense;

typedef struct s_expense_list {
	Expense records[MAX_EXPENSES];
	int     count;
	int     max_id;
}   ExpenseList;

/* 
    Moduli che si appoggiano:

    main.c — solo load, menu, save

    parser.c — implementa parse_line, validatori

    menu.c — run_interactive_menu e tutte le funzioni associate

    summary.c — show_summary, compute statistics

    io_utils.c — stampa singole spese, input validato

    expense_utils.c — cerca per ID, gestisce free/allocazioni 

*/

/* === File I/O === */
int  load_expenses_from_file(const char *filename, ExpenseList *list);
int  save_expenses_to_file(const char *filename, ExpenseList *list);

/* === Parsing === */
bool parse_line(const char *line, Expense *expense, ExpenseList *list);
bool is_valid_date(const char *date);
bool is_valid_amount(const char *amount_str, float *amount_out);
bool is_valid_id(const char *id_str, int *id_out, ExpenseList *list);

/* === Interfaccia utente === */
void run_interactive_menu(ExpenseList *list);

/* === Operazioni utente === */
void list_expenses(const ExpenseList *list);
void add_expense(ExpenseList *list);
void edit_expense(ExpenseList *list);
void delete_expense(ExpenseList *list);
void search_by_category(const ExpenseList *list);
void search_by_date_range(const ExpenseList *list);
void show_summary(const ExpenseList *list);

/* === Utility === */
Expense *find_expense_by_id(ExpenseList *list, int id);
void print_expense(const Expense *e);
void free_expense(Expense *e); // se si usano strdup()

#endif
