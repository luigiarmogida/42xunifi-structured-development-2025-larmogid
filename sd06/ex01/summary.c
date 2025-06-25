#include <stdlib.h>
#include <string.h>
#include "expense.h"

static int find_category_index(t_summary *summary, const char *category) {
    for (int i = 0; i < summary->category_count; i++) {
        if (strcmp(summary->categories[i].category, category) == 0)
            return i;
    }
    return -1;
}

void compute_summary(const t_expense_list *list, t_summary *summary) {
    summary->record_count = list->count;
    summary->total_amount = 0.0f;
    summary->average = 0.0f;
    summary->category_count = 0;
    summary->categories = malloc(sizeof(t_category_summary) * list->count);
    if (!summary->categories)
        return;

    for (int i = 0; i < list->count; i++) {
        t_expense exp = list->expenses[i];
        summary->total_amount += exp.amount;

        char *cat_lc = to_lowercase(exp.category);
        int index = find_category_index(summary, cat_lc);

        if (index == -1) {
            index = summary->category_count++;
            summary->categories[index].category = strdup(cat_lc);
            summary->categories[index].total = 0.0f;
        }

        summary->categories[index].total += exp.amount;
        free(cat_lc);
    }

    if (list->count > 0)
        summary->average = summary->total_amount / list->count;

    for (int i = 0; i < summary->category_count; i++) {
        summary->categories[i].percentage =
            (summary->total_amount > 0.0f)
            ? (summary->categories[i].total / summary->total_amount) * 100.0f
            : 0.0f;
    }
}

void free_summary(t_summary *summary) {
    if (!summary || !summary->categories)
        return;
    for (int i = 0; i < summary->category_count; i++) {
        free(summary->categories[i].category);
    }
    free(summary->categories);
    summary->categories = NULL;
    summary->category_count = 0;
}
