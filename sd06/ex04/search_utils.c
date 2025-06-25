#include "expense_tracker.h"
#include <stdio.h>
#include <string.h>
#include <strings.h> // strcasestr (non standard, ma utile)

void search_by_category(const ExpenseList *list) {
    if (list->count == 0) {
        printf("No expenses to search.\n");
        return;
    }

    char buffer[256];
    printf("Enter category substring to search: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return;
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    if (strlen(buffer) == 0) {
        printf("Empty input — cancelled.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < list->count; i++) {
        const Expense *e = &list->records[i];
        if (strstr(e->category, buffer)) {
            print_expense(e);
            found++;
        }
    }

    if (found == 0)
        printf("No expenses found matching '%s'.\n", buffer);
    else
        printf("%d matching expense(s) found.\n", found);
}

void search_by_date_range(const ExpenseList *list) {
    if (list->count == 0) {
        printf("No expenses to search.\n");
        return;
    }

    char start[64], end[64];
    printf("Enter start date (YYYY-MM-DD): ");
    if (!fgets(start, sizeof(start), stdin)) return;
    size_t len = strlen(start);
    if (len > 0 && start[len - 1] == '\n') start[len - 1] = '\0';
    if (!is_valid_date(start)) {
        printf("Invalid start date.\n");
        return;
    }

    printf("Enter end date (YYYY-MM-DD): ");
    if (!fgets(end, sizeof(end), stdin)) return;
    len = strlen(end);
    if (len > 0 && end[len - 1] == '\n') end[len - 1] = '\0';
    if (!is_valid_date(end)) {
        printf("Invalid end date.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < list->count; i++) {
        const Expense *e = &list->records[i];
        if (strcmp(e->date, start) >= 0 && strcmp(e->date, end) <= 0) {
            print_expense(e);
            found++;
        }
    }

    if (found == 0)
        printf("No expenses found in range %s to %s.\n", start, end);
    else
        printf("%d expense(s) found in range.\n", found);
}
