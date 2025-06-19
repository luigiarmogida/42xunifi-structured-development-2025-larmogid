#include "expense_tracker.h"
#include <stdio.h>     // per printf, scanf, getchar, fgets
#include <string.h>    // per strtok, strncpy, strcspn, strcasestr
#include <stdlib.h>       // per atoi, ecc

int delete_expense(ExpenseTracker *tracker, int id) {
    for (int i = 0; i < tracker->count; i++) {
        if (tracker->expenses[i].id == id) {
            printf("Confirm deletion of expense ID %d? (y/n): ", id);
            char c = getchar();
            while (getchar() != '\n');
            if (c == 'y' || c == 'Y') {
                for (int j = i; j < tracker->count - 1; j++)
                    tracker->expenses[j] = tracker->expenses[j + 1];
                tracker->count--;
                printf("Expense ID %d deleted.\n", id);
                return 0;
            } else {
                printf("Deletion cancelled.\n");
                return -1;
            }
        }
    }
    printf("Expense ID %d not found.\n", id);
    return -1;
}