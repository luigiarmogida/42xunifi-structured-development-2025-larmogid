#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expense.h"

static void read_line(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
    }
}

void prompt_filter(t_filter *filter) {
    char input[128];

    while (1) {
        printf("\nFilter options:\n");
        printf("1. All expenses\n");
        printf("2. By category (partial match)\n");
        printf("3. By date range (YYYY-MM-DD to YYYY-MM-DD)\n");
        printf("Choose an option (1/2/3): ");
        read_line(input, sizeof(input));

        if (strcmp(input, "1") == 0) {
            filter->type = FILTER_ALL;
            return;
        }

        if (strcmp(input, "2") == 0) {
            filter->type = FILTER_CATEGORY;
            printf("Enter category filter: ");
            read_line(input, sizeof(input));
            char *trimmed = trim_whitespace(input);
            if (strlen(trimmed) > 0) {
                filter->category = to_lowercase(trimmed);
                return;
            } else {
                printf("Empty input is not valid.\n");
            }
        }

        if (strcmp(input, "3") == 0) {
            filter->type = FILTER_DATES;
            while (1) {
                printf("Start date (YYYY-MM-DD): ");
                read_line(filter->start_date, sizeof(filter->start_date));
                if (!is_valid_date_format(filter->start_date)) {
                    printf("Invalid format. Try again.\n");
                    continue;
                }

                printf("End date (YYYY-MM-DD): ");
                read_line(filter->end_date, sizeof(filter->end_date));
                if (!is_valid_date_format(filter->end_date)) {
                    printf("Invalid format. Try again.\n");
                    continue;
                }

                if (compare_dates(filter->start_date, filter->end_date) > 0) {
                    printf("Start date must not be after end date.\n");
                    continue;
                }

                return;
            }
        }

        printf("Invalid selection. Try again.\n");
    }
}
