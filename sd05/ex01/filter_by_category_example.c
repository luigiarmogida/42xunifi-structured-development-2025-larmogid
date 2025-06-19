#include <stdio.h>
#include <string.h>
#include "expense_tracker.h"

void filter_by_category(const ExpenseTracker *tracker, const char *substring) {
    int found = 0;
    for (int i = 0; i < tracker->count; i++) {
        // strstr (case-sensitive)
        if (strstr(tracker->expenses[i].category, substring)) {
            if (!found) {
                printf("\nFiltered by category containing '%s':\n", substring);
                printf("%-5s %-10s %-10s %-15s %-s\n", "ID", "Date", "Amount", "Category", "Description");
                printf("-------------------------------------------------------------------------------\n");
            }
            found = 1;
            Expense e = tracker->expenses[i];
            printf("%-5d %-10s %-10.2f %-15s %-s\n",
                   e.id, e.date, e.amount, e.category, e.description);
        }
    }
    if (!found)
        printf("No expenses found matching category substring '%s'.\n", substring);
}