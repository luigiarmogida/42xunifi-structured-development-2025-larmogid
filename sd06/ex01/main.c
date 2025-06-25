#include <stdio.h>
#include <stdlib.h>
#include "expense.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expenses_file>\n", argv[0]);
        return 1;
    }

    t_expense_list all_expenses;
    if (!load_expenses_from_file(argv[1], &all_expenses)) {
        fprintf(stderr, "Failed to load expenses from file.\n");
        return 1;
    }

    t_filter filter;
    prompt_filter(&filter);

    t_expense_list filtered;
    filter_expenses(&all_expenses, &filter, &filtered);

    t_summary summary;
    compute_summary(&filtered, &summary);
    print_summary(&summary);

    free_summary(&summary);

    // Se hai allocazioni per category/description, liberale qui
    for (int i = 0; i < all_expenses.count; i++) {
        free(all_expenses.expenses[i].category);
        free(all_expenses.expenses[i].description);
    }

    if (filter.type == FILTER_CATEGORY)
        free(filter.category);

    return 0;
}
