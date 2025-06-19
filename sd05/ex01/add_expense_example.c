// add_expense.c (implementazione semplificata)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expense_tracker.h"

int add_expense(ExpenseTracker *tracker) {
    if (tracker->count >= MAX_EXPENSES) {
        printf("Cannot add more expenses (limit reached).\n");
        return -1;
    }

    Expense e;
    e.id = ++(tracker->max_id);

    printf("Date (YYYY-MM-DD): ");
    fgets(e.date, DATE_STR_LEN, stdin);
    e.date[strcspn(e.date, "\n")] = 0;

    printf("Amount: ");
    if (scanf("%f", &e.amount) != 1 || e.amount <= 0) {
        printf("Invalid amount.\n");
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');

    printf("Category: ");
    fgets(e.category, MAX_CATEGORY_LEN, stdin);
    e.category[strcspn(e.category, "\n")] = 0;

    if (strlen(e.category) == 0) {
        printf("Category cannot be empty.\n");
        return -1;
    }

    printf("Description (optional): ");
    fgets(e.description, MAX_DESC_LEN, stdin);
    e.description[strcspn(e.description, "\n")] = 0;

    tracker->expenses[tracker->count++] = e;
    printf("Expense added with ID %d.\n", e.id);
    return 0;
}
