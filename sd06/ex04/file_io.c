#include "expense_tracker.h"
#include "get_next_line.h" 
#include <stdio.h>

int load_expenses_from_file(const char *filename, ExpenseList *list) {
    FILE *file;
    char *line;
    int loaded = 0;
    int skipped = 0;

    list->count = 0;
    list->max_id = 0;

    file = fopen(filename, "r");
    if (!file) {
        printf("Error: cannot open file '%s'\n", filename);
        return -1;
    }

    int fd = fileno(file);  // otteniamo il file descriptor
    while ((line = get_next_line(fd)) != NULL) {
        if (list->count >= MAX_EXPENSES) {
            printf("Warning: maximum number of expenses (%d) reached.\n", MAX_EXPENSES);
            free(line);
            break;
        }

        Expense e;
        if (parse_line(line, &e, list)) {
            list->records[list->count++] = e;
            loaded++;
        } else {
            printf("Warning: skipped invalid line → %s", line);
            skipped++;
        }
        free(line);
    }

    fclose(file);
    printf("Loaded %d valid expenses (%d skipped).\n", loaded, skipped);
    return loaded;
}

int save_expenses_to_file(const char *filename, ExpenseList *list) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: cannot write to file '%s'\n", filename);
        return -1;
    }

    for (int i = 0; i < list->count; i++) {
        Expense *e = &list->records[i];
        fprintf(file, "%d,%s,%.2f,%s,%s\n",
                e->id, e->date, e->amount, e->category, e->description);
    }

    fclose(file);
    printf("Saved %d expenses to '%s'\n", list->count, filename);
    return 0;
}

