#ifndef EXPENSE_OPS_H
#define EXPENSE_OPS_H

#include "expense_tracker.h"

// Parsing
int load_expenses(ExpenseTracker *tracker, const char *filename);

// Aggiunta, modifica, rimozione -> Operazioni CRUD (Create/Read/Update/Delete)
int add_expense(ExpenseTracker *tracker); /* Create */
int edit_expense(ExpenseTracker *tracker, int id); /* Update */
int delete_expense(ExpenseTracker *tracker, int id); /* Delete */
void list_expenses(const ExpenseTracker *tracker); /*  Read */

/* Filtri */
void filter_by_category(const ExpenseTracker *tracker, const char *substring);
void filter_by_date_range(const ExpenseTracker *tracker, const char *start_date, const char *end_date);

// Riepilogo
void show_summary(const ExpenseTracker *tracker);

// Scrittura su file
int save_expenses(const ExpenseTracker *tracker);

int id_exists(ExpenseTracker *tracker, int id);

#endif


