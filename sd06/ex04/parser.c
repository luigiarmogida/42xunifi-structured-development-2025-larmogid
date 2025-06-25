#include "expense_tracker.h"
#include <ctype.h>  // isdigit
#include <limits.h> // INT_MAX

// Rimuove newline finale, se presente
static void strip_newline(char *str) {
    size_t len = strlen(str);
    if (len && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

static bool is_number(const char *str) {
    if (!str || !*str) return false;
    for (int i = 0; str[i]; ++i) {
        if (!isdigit((unsigned char)str[i]))
            return false;
    }
    return true;
}

bool is_valid_date(const char *date) {
    int y, m, d;
    if (sscanf(date, "%4d-%2d-%2d", &y, &m, &d) != 3)
        return false;
    if (y < 1900 || y > 2100 || m < 1 || m > 12 || d < 1 || d > 31)
        return false;
    return true;
}

bool is_valid_amount(const char *amount_str, float *amount_out) {
    char *end;
    float val = strtof(amount_str, &end);
    if (end == amount_str || val <= 0.0f)
        return false;
    if (amount_out)
        *amount_out = val;
    return true;
}

bool is_valid_id(const char *id_str, int *id_out, ExpenseList *list) {
    if (!is_number(id_str))
        return false;
    int id = atoi(id_str);
    if (id <= 0)
        return false;
    // Verifica collisioni
    for (int i = 0; i < list->count; i++) {
        if (list->records[i].id == id)
            return false;
    }
    if (id_out)
        *id_out = id;
    return true;
}

bool parse_line(const char *line, Expense *expense, ExpenseList *list) {
    char buffer[MAX_LINE_LEN];
    char *tokens[5];
    int fields = 0;

    strncpy(buffer, line, MAX_LINE_LEN - 1);
    buffer[MAX_LINE_LEN - 1] = '\0';
    strip_newline(buffer);

    char *token = strtok(buffer, ",");
    while (token && fields < 5) {
        tokens[fields++] = token;
        token = strtok(NULL, ",");
    }

    // Vecchio formato: 4 campi (senza ID)
    if (fields == 4) {
        expense->id = ++list->max_id;
        expense->date = strdup(tokens[0]);
        if (!is_valid_date(expense->date)) return false;

        if (!is_valid_amount(tokens[1], &expense->amount)) return false;
        if (!tokens[2] || !*tokens[2]) return false;
        expense->category = strdup(tokens[2]);
        expense->description = tokens[3] ? strdup(tokens[3]) : strdup("");
        return true;
    }

    // Nuovo formato: 5 campi (con ID)
    if (fields == 5) {
        int id;
        if (!is_valid_id(tokens[0], &id, list)) return false;
        expense->id = id;
        if (id > list->max_id)
            list->max_id = id;

        expense->date = strdup(tokens[1]);
        if (!is_valid_date(expense->date)) return false;

        if (!is_valid_amount(tokens[2], &expense->amount)) return false;
        if (!tokens[3] || !*tokens[3]) return false;
        expense->category = strdup(tokens[3]);
        expense->description = tokens[4] ? strdup(tokens[4]) : strdup("");
        return true;
    }

    return false; // Righe con numero di campi errato
}
