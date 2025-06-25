#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "expense.h"
#include "get_next_line.h"

// Parsing del file CSV

// --- Supporto locale (trim, duplicate, etc.) ---
static char *str_duplicate_trimmed(const char *src) {
    char *tmp = strdup(src);
    if (!tmp) return NULL;
    char *trimmed = trim_whitespace(tmp);
    char *result = strdup(trimmed);
    free(tmp);
    return result;
}

// --- Parsing di una singola riga CSV ---
int parse_line(const char *line, t_expense *exp) {
    char *dup = strdup(line);
    if (!dup) return 0;

    char *token;
    char *fields[4] = { NULL };
    int i = 0;

    token = strtok(dup, ",");
    while (token && i < 4) {
        fields[i++] = token;
        token = strtok(NULL, ",");
    }

    if (i < 4) {
        print_warning("Line skipped: not enough fields.");
        free(dup);
        return 0;
    }

    // Trim and validate date
    char *date = trim_whitespace(fields[0]);
    if (!is_valid_date_format(date)) {
        print_warning("Line skipped: invalid date format.");
        free(dup);
        return 0;
    }
    strncpy(exp->date, date, 11);
    exp->date[10] = '\0';

    // Parse and validate amount
    char *endptr;
    float amount = strtof(fields[1], &endptr);
    if (amount <= 0 || *endptr != '\0') {
        print_warning("Line skipped: invalid or negative amount.");
        free(dup);
        return 0;
    }
    exp->amount = amount;

    // Parse and normalize category
    exp->category = to_lowercase(trim_whitespace(fields[2]));

    // Parse and trim description
    exp->description = str_duplicate_trimmed(fields[3]);

    free(dup);
    return 1;
}

// --- Caricamento da file ---
int load_expenses_from_file(const char *filename, t_expense_list *list) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        print_warning("Error: cannot open file.");
        return 0;
    }

    char *line;
    while ((line = get_next_line(fileno(fp))) != NULL) {
        if (list->count >= MAX_EXPENSES) {
            print_warning("Reached maximum number of records.");
            break;
        }
        t_expense exp;
        if (parse_line(line, &exp)) {
            list->expenses[list->count++] = exp;
        }
        free(line);
    }

    fclose(fp);
    return 1;
}
