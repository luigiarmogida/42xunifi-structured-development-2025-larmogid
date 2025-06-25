#include "expense_tracker.h"

void free_expense_list(ExpenseList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->records[i].date);
        free(list->records[i].category);
        free(list->records[i].description);
    }
    list->count = 0;
    list->max_id = 0;
}
