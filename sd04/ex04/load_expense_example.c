#include "expense_tracker.h"
#include <stdio.h>

/* 
* Legge il file riga per riga.
* Supporta sia il formato a 4 che a 5 campi.
* Verifica ID duplicati e assegna nuovi ID quando necessario.
* Salta righe malformate con un messaggio di errore.
*/

int load_expenses(ExpenseTracker *tracker, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        Expense e;
        int id_given = 0;
        char *fields[5];
        char *tok = strtok(line, ",\n");
        int i = 0;
        while (tok && i < 5) {
            fields[i++] = tok;
            tok = strtok(NULL, ",\n");
        }

        if (i == 4) { // old format
            e.id = ++tracker->max_id;
            strncpy(e.date, fields[0], DATE_STR_LEN);
            e.amount = atof(fields[1]);
            strncpy(e.category, fields[2], MAX_CATEGORY_LEN);
            strncpy(e.description, fields[3], MAX_DESC_LEN);
        } else if (i == 5) { // new format
            int id = atoi(fields[0]);
            if (id <= 0 || id_exists(tracker, id)) {
                fprintf(stderr, "Skipping line with invalid or duplicate ID: %s\n", line);
                continue;
            }
            e.id = id;
            if (e.id > tracker->max_id)
                tracker->max_id = e.id;
            strncpy(e.date, fields[1], DATE_STR_LEN);
            e.amount = atof(fields[2]);
            strncpy(e.category, fields[3], MAX_CATEGORY_LEN);
            strncpy(e.description, fields[4], MAX_DESC_LEN);
        } else {
            fprintf(stderr, "Skipping malformed line: %s\n", line);
            continue;
        }

        if (tracker->count < MAX_EXPENSES)
            tracker->expenses[tracker->count++] = e;
        else {
            fprintf(stderr, "Too many records, skipping rest.\n");
            break;
        }
    }
    fclose(fp);
    return 0;
}
