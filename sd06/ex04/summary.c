#include "expense_tracker.h"
#include <stdio.h>
#include <string.h>

typedef struct s_category_total {
    char *category;
    float total;
} CategoryTotal;

#define MAX_CATEGORIES 100

void show_summary(const ExpenseList *list) {
    if (list->count == 0) {
        printf("No expenses to summarize.\n");
        return;
    }

    float total_amount = 0.0f;
    int total_count = list->count;

    CategoryTotal categories[MAX_CATEGORIES];
    int cat_count = 0;

    // Accumulo
    for (int i = 0; i < list->count; i++) {
        const Expense *e = &list->records[i];
        total_amount += e->amount;

        // Cerca categoria
        int found = 0;
        for (int j = 0; j < cat_count; j++) {
            if (strcmp(categories[j].category, e->category) == 0) {
                categories[j].total += e->amount;
                found = 1;
                break;
            }
        }
        // Nuova categoria
        if (!found && cat_count < MAX_CATEGORIES) {
            categories[cat_count].category = e->category;
            categories[cat_count].total = e->amount;
            cat_count++;
        }
    }

    // Output generale
    float average = total_amount / total_count;
    printf("\nSummary:\n");
    printf("Total expenses: %d\n", total_count);
    printf("Total amount: %.2f\n", total_amount);
    printf("Average amount: %.2f\n", average);

    // Breakdown per categoria
    printf("\nBy category:\n");
    printf("%-20s | %-10s | %-10s\n", "Category", "Total", "Percent");
    printf("---------------------------------------------\n");

    for (int i = 0; i < cat_count; i++) {
        float percent = (categories[i].total / total_amount) * 100.0f;
        printf("%-20s | %-10.2f | %-9.2f%%\n",
                  categories[i].category,
                  categories[i].total,
                  percent);
    }
}
