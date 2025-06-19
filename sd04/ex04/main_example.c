// main.c (sintesi)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expense_tracker.h"
#include "expense_ops.h"

void print_menu(void) {
    printf("\nExpense Tracker Menu:\n");
    printf("1. List all expenses\n");
    printf("2. Filter by category\n");
    printf("3. Filter by date range\n");
    printf("4. Add new expense\n");
    printf("5. Edit expense\n");
    printf("6. Delete expense\n");
    printf("7. Show summary\n");
    printf("8. Save and exit\n");
    printf("Select an option: ");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expenses_file.csv>\n", argv[0]);
        return 1;
    }

    ExpenseTracker tracker = {.count = 0, .max_id = 0, .filename = argv[1]};
    if (load_expenses(&tracker, tracker.filename) != 0) {
        fprintf(stderr, "Failed to load expenses.\n");
        return 1;
    }

    int choice;
    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) break;
        while (getchar() != '\n'); // flush input

        if (choice == 1)
            list_expenses(&tracker);
        else if (choice == 2) {
            char cat[50];
            printf("Enter category substring: ");
            fgets(cat, sizeof(cat), stdin);
            cat[strcspn(cat, "\n")] = 0;
            filter_by_category(&tracker, cat);
        } else if (choice == 3) {
            char start[11], end[11];
            printf("Start date (YYYY-MM-DD): "); fgets(start, 11, stdin);
            while (getchar() != '\n');
            printf("End date (YYYY-MM-DD): "); fgets(end, 11, stdin);
            filter_by_date_range(&tracker, start, end);
        } else if (choice == 4)
            add_expense(&tracker);
        else if (choice == 5) {
            int id; printf("Enter ID to edit: "); scanf("%d", &id);
            edit_expense(&tracker, id);
        } else if (choice == 6) {
            int id; printf("Enter ID to delete: "); scanf("%d", &id);
            delete_expense(&tracker, id);
        } else if (choice == 7)
            show_summary(&tracker);
        else if (choice == 8) {
            save_expenses(&tracker);
            break;
        }
    }

    return 0;
}