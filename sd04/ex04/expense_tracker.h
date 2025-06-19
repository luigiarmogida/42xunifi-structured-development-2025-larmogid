#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#define MAX_EXPENSES 1000
#define MAX_CATEGORY_LEN 50
#define MAX_DESC_LEN 100
#define DATE_STR_LEN 11 // YYYY-MM-DD

typedef struct s_expense {
    int id;
    char date[DATE_STR_LEN];
    float amount;
    char category[MAX_CATEGORY_LEN];
    char description[MAX_DESC_LEN];
} Expense;

typedef struct s_tracker {
    Expense expenses[MAX_EXPENSES];
    int count;
    int max_id;
    char *filename;
} ExpenseTracker;

#endif
