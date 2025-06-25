#include <string.h>
#include <stdlib.h>
#include "expense.h"

int matches_filter(const t_expense *exp, const t_filter *filter) {
    if (filter->type == FILTER_ALL)
        return 1;

    if (filter->type == FILTER_CATEGORY) {
        char *exp_cat_lc = to_lowercase(exp->category);
        int match = (strstr(exp_cat_lc, filter->category) != NULL);
        free(exp_cat_lc);
        return match;
    }

    if (filter->type == FILTER_DATES) {
        if (compare_dates(exp->date, filter->start_date) < 0)
            return 0;
        if (compare_dates(exp->date, filter->end_date) > 0)
            return 0;
        return 1;
    }

    return 0;
}

void filter_expenses(const t_expense_list *input, const t_filter *filter, t_expense_list *output) {
    output->count = 0;
    for (int i = 0; i < input->count; i++) {
        if (matches_filter(&input->expenses[i], filter)) {
            output->expenses[output->count++] = input->expenses[i];
        }
    }
}
