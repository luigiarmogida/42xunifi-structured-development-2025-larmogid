#include "expense_tracker.h"
#include <stdio.h>
#include <string.h>    // per strtok, strncpy, strcspn, strcasestr

int edit_expense(ExpenseTracker *tracker, int id) {
    for (int i = 0; i < tracker->count; i++) {
        if (tracker->expenses[i].id == id) {
            Expense *e = &tracker->expenses[i];
            printf("Editing expense ID %d:\n", id);
            printf("Current date: %s\nNew date (blank to keep): ", e->date);
            char buf[DATE_STR_LEN];
            fgets(buf, DATE_STR_LEN, stdin);
            if (buf[0] != '\n') {
                buf[strcspn(buf, "\n")] = 0;
                strncpy(e->date, buf, DATE_STR_LEN);
            }

            printf("Current amount: %.2f\nNew amount (<= 0 to keep): ", e->amount);
            float new_amt;
            if (scanf("%f", &new_amt) == 1 && new_amt > 0)
                e->amount = new_amt;
            while (getchar() != '\n');

            printf("Current category: %s\nNew category (blank to keep): ", e->category);
            fgets(buf, MAX_CATEGORY_LEN, stdin);
            if (buf[0] != '\n') {
                buf[strcspn(buf, "\n")] = 0;
                strncpy(e->category, buf, MAX_CATEGORY_LEN);
            }

            printf("Current description: %s\nNew description (blank to keep): ", e->description);
            fgets(buf, MAX_DESC_LEN, stdin);
            if (buf[0] != '\n') {
                buf[strcspn(buf, "\n")] = 0;
                strncpy(e->description, buf, MAX_DESC_LEN);
            }

            printf("Expense ID %d updated.\n", id);
            return 0;
        }
    }
    printf("Expense ID %d not found.\n", id);
    return -1;
}