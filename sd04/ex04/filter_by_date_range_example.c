#include <stdio.h>
#include <string.h>
#include "expense_tracker.h"

int date_in_range(const char *date, const char *start, const char *end) {
    return strcmp(date, start) >= 0 && strcmp(date, end) <= 0;
}

void filter_by_date_range(const ExpenseTracker *tracker, const char *start_date, const char *end_date) {
    int found = 0;
    for (int i = 0; i < tracker->count; i++) {
        if (date_in_range(tracker->expenses[i].date, start_date, end_date)) {
            if (!found) {
                printf("\nFiltered by date range %s to %s:\n", start_date, end_date);
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
        printf("No expenses found in date range %s to %s.\n", start_date, end_date);
}