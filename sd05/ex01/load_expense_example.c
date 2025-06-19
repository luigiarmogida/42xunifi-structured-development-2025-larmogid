#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expense_tracker.h"
#include "expense_ops.h"

int load_expenses(ExpenseTracker *tracker, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    printf("Opened file: %s\n", filename);

    char line[256];
    int lines_read = 0;
    while (fgets(line, sizeof(line), fp)) {
        lines_read++;
        printf("\nLine %d: %s", lines_read, line);

        Expense e;
        char *fields[5] = {NULL};
        int f = 0;

        char *tok = strtok(line, ",\n");
        while (tok && f < 5) {
            fields[f] = tok;
            printf("  Field[%d]: %s\n", f, tok);
            f++;
            tok = strtok(NULL, ",\n");
        }

        if (f == 5) {
            int id = atoi(fields[0]);
            printf("  Parsed ID: %d\n", id);
            if (id <= 0 || id_exists(tracker, id)) {
                printf("  Skipping invalid or duplicate ID: %d\n", id);
                continue;
            }
            e.id = id;
            strncpy(e.date, fields[1], DATE_STR_LEN);
            e.amount = atof(fields[2]);
            strncpy(e.category, fields[3], MAX_CATEGORY_LEN);
            strncpy(e.description, fields[4], MAX_DESC_LEN);

            tracker->expenses[tracker->count++] = e;
            if (e.id > tracker->max_id)
                tracker->max_id = e.id;

            printf("  -> Expense added: ID=%d, Date=%s, Amount=%.2f, Category=%s, Description=%s\n",
                   e.id, e.date, e.amount, e.category, e.description);
        } else {
            printf("  Skipping malformed line (found %d fields instead of 5).\n", f);
        }
    }

    fclose(fp);

    printf("Finished loading. Total expenses loaded: %d\n", tracker->count);

    return 1;
}

int id_exists(ExpenseTracker *tracker, int id) {
    for (int i = 0; i < tracker->count; ++i)
        if (tracker->expenses[i].id == id)
            return 1;
    return 0;
}