#include <stdio.h>
#include <string.h>
#include "expense_tracker.h"

typedef struct {
    char category[MAX_CATEGORY_LEN];
    float total;
    int count;
} CategorySummary;

void show_summary(const ExpenseTracker *tracker) {
    if (tracker->count == 0) {
        printf("No expenses to summarize.\n");
        return;
    }

    float total_spent = 0;
    int total_count = tracker->count;
    CategorySummary summaries[MAX_EXPENSES];
    int unique_categories = 0;

    for (int i = 0; i < tracker->count; i++) {
        Expense e = tracker->expenses[i];
        total_spent += e.amount;

        int found = 0;
        for (int j = 0; j < unique_categories; j++) {
            if (strcmp(summaries[j].category, e.category) == 0) {
                summaries[j].total += e.amount;
                summaries[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(summaries[unique_categories].category, e.category, MAX_CATEGORY_LEN);
            summaries[unique_categories].total = e.amount;
            summaries[unique_categories].count = 1;
            unique_categories++;
        }
    }

    printf("\nSummary:\n");
    printf("Total expenses: %d\n", total_count);
    printf("Total amount spent: %.2f\n", total_spent);
    printf("Average expense: %.2f\n", total_spent / total_count);
    printf("\nBreakdown by category:\n");
    for (int i = 0; i < unique_categories; i++) {
        float pct = (summaries[i].total / total_spent) * 100;
        printf("%-15s: %.2f (%d entries, %.1f%%)\n",
               summaries[i].category,
               summaries[i].total,
               summaries[i].count,
               pct);
    }
}
