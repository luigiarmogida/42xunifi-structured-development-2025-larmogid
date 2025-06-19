// list_expenses.c
#include <stdio.h>
#include "expense_tracker.h"

void list_expenses(const ExpenseTracker *tracker) {
    if (tracker->count == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\n%-5s %-10s %-10s %-15s %-s\n", "ID", "Date", "Amount", "Category", "Description");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < tracker->count; i++) {
        Expense e = tracker->expenses[i];
        printf("%-5d %-10s %-10.2f %-15s %-s\n",
               e.id, e.date, e.amount, e.category, e.description);
    }
}