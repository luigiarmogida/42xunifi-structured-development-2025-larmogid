// save_expenses.c
#include "expense_tracker.h"
#include <stdio.h>

int save_expenses(const ExpenseTracker *tracker) {
    FILE *fp = fopen(tracker->filename, "w");
    if (!fp) {
        perror("fopen");
        return -1;
    }
    for (int i = 0; i < tracker->count; i++) {
        Expense e = tracker->expenses[i];
        fprintf(fp, "%d,%s,%.2f,%s,%s\n", e.id, e.date, e.amount, e.category, e.description);
    }
    fclose(fp);
    printf("Expenses saved to %s.\n", tracker->filename);
    return 0;
}