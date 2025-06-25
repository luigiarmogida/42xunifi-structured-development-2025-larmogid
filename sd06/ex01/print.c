#include <stdio.h>
#include "expense.h"

void print_summary(const t_summary *summary) {
    if (summary->record_count == 0) {
        printf("\nNo matching expenses found.\n");
        return;
    }

    printf("\nSummary of expenses:\n");
    printf("---------------------\n");
    printf("Total records: %d\n", summary->record_count);
    printf("Total spent: %.2f €\n", summary->total_amount);
    printf("Average expense: %.2f €\n", summary->average);
    printf("\nBreakdown by category:\n");

    for (int i = 0; i < summary->category_count; i++) {
        printf(" - %s: %.2f € (%.1f%%)\n",
               summary->categories[i].category,
               summary->categories[i].total,
               summary->categories[i].percentage);
    }
    printf("\n");
}
