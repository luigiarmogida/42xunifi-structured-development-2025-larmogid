#include "expense_tracker.h"
#include <stdio.h>   // scanf, getchar
#include <string.h>  // strcmp
#include "search_utils.h"


static void print_menu(void) {
    printf("\nExpense Tracker Menu:\n");
    printf("1. List all expenses\n");
    printf("2. Search by category\n");
    printf("3. Search by date range\n");
    printf("4. Add new expense\n");
    printf("5. Edit an expense\n");
    printf("6. Delete an expense\n");
    printf("7. Show summary\n");
    printf("8. Save and exit\n");
    printf("> ");
}

void run_interactive_menu(ExpenseList *list) {
    int choice = 0;
    char buffer[32];

    while (1) {
        print_menu();

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Error: input failed.\n");
            continue;
        }
        choice = atoi(buffer);

        switch (choice) {
            case 1:
                list_expenses(list);
                break;
            case 2:
                search_by_category(list);
                break;
            case 3:
                search_by_date_range(list);
                break;
            case 4:
                add_expense(list);
                break;
            case 5:
                edit_expense(list);
                break;
            case 6:
                delete_expense(list);
                break;
            case 7:
                show_summary(list);
                break;
            case 8:
                printf("Saving and exiting...\n");
                return;
            default:
                printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }
    }
}

/* list_expense */

void print_expense(const Expense *e) {
    printf("ID: %d | Date: %s | Amount: %.2f | Category: %s | Description: %s\n",
              e->id, e->date, e->amount, e->category, e->description);
}

void list_expenses(const ExpenseList *list) {
    if (list->count == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\n%-4s | %-10s | %-8s | %-15s | %s\n", "ID", "Date", "Amount", "Category", "Description");
    printf("---------------------------------------------------------------\n");

    // Spese già ordinate per ID nel caricamento → stampa diretta
    for (int i = 0; i < list->count; i++) {
        const Expense *e = &list->records[i];
        printf("%-4d | %-10s | %-8.2f | %-15s | %s\n",
                  e->id, e->date, e->amount, e->category, e->description);
    }
}

static void prompt_string(const char *msg, char *dest, size_t max_len) {
    while (1) {
        printf("%s", msg);
        if (!fgets(dest, max_len, stdin)) {
            printf("Error: input failed.\n");
            continue;
        }
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n')
            dest[len - 1] = '\0';
        if (strlen(dest) > 0)
            break;
        printf("Input cannot be empty. Try again.\n");
    }
}

void add_expense(ExpenseList *list) {
    if (list->count >= MAX_EXPENSES) {
        printf("Cannot add more expenses: limit reached.\n");
        return;
    }

    char buffer[256];
    Expense e;

    // --- Data ---
    while (1) {
        prompt_string("Enter date (YYYY-MM-DD): ", buffer, sizeof(buffer));
        if (is_valid_date(buffer)) {
            e.date = strdup(buffer);
            break;
        }
        printf("Invalid date format.\n");
    }

    // --- Amount ---
    while (1) {
        prompt_string("Enter amount: ", buffer, sizeof(buffer));
        if (is_valid_amount(buffer, &e.amount))
            break;
        printf("Invalid amount. Must be a positive number.\n");
    }

    // --- Categoria ---
    while (1) {
        prompt_string("Enter category: ", buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            e.category = strdup(buffer);
            break;
        }
        printf("Category cannot be empty.\n");
    }

    // --- Descrizione (opzionale) ---
    prompt_string("Enter description (optional): ", buffer, sizeof(buffer));
    e.description = strdup(buffer);  // può essere stringa vuota

    // --- Assegna ID e salva ---
    e.id = ++list->max_id;
    list->records[list->count++] = e;

    printf("Expense added with ID %d.\n", e.id);
}

static void prompt_edit_field(const char *field_name, char *current_value, char **target) {
    char buffer[256];

    printf("%s [%s]: ", field_name, current_value);
    if (!fgets(buffer, sizeof(buffer), stdin))
        return;
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    if (strlen(buffer) > 0) {
        free(*target);
        *target = strdup(buffer);
    }
}

static void prompt_edit_float(const char *field_name, float *value) {
    char buffer[256];

    printf("%s [%.2f]: ", field_name, *value);
    if (!fgets(buffer, sizeof(buffer), stdin))
        return;
    if (buffer[0] == '\n') return;

    float tmp;
    if (is_valid_amount(buffer, &tmp))
        *value = tmp;
    else
        printf("Invalid input: amount unchanged.\n");
}

void edit_expense(ExpenseList *list) {
    if (list->count == 0) {
        printf("No expenses to edit.\n");
        return;
    }

    char buffer[64];
    int id;

    printf("Enter ID of the expense to edit: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return;
    id = atoi(buffer);
    if (id <= 0) {
        printf("Invalid ID.\n");
        return;
    }

    Expense *e = find_expense_by_id(list, id);
    if (!e) {
        printf("No expense found with ID %d.\n", id);
        return;
    }

    printf("Editing expense ID %d:\n", e->id);
    print_expense(e);

    // Edit: Date
    while (1) {
        printf("Date [%s]: ", e->date);
        if (!fgets(buffer, sizeof(buffer), stdin)) return;
        if (buffer[0] == '\n') break;  // keep current
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        if (is_valid_date(buffer)) {
            free(e->date);
            e->date = strdup(buffer);
            break;
        } else {
            printf("Invalid date format. Try again.\n");
        }
    }

    // Edit: Amount
    prompt_edit_float("Amount", &e->amount);

    // Edit: Category
    prompt_edit_field("Category", e->category, &e->category);

    // Edit: Description
    prompt_edit_field("Description", e->description, &e->description);

    printf("Expense ID %d updated.\n", e->id);
}

void delete_expense(ExpenseList *list) {
    if (list->count == 0) {
        printf("No expenses to delete.\n");
        return;
    }

    char buffer[64];
    int id;

    printf("Enter ID of the expense to delete: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return;
    id = atoi(buffer);
    if (id <= 0) {
        printf("Invalid ID.\n");
        return;
    }

    int index = -1;
    for (int i = 0; i < list->count; i++) {
        if (list->records[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("No expense found with ID %d.\n", id);
        return;
    }

    printf("Found expense:\n");
    print_expense(&list->records[index]);

    printf("Are you sure you want to delete this expense? (y/n): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return;
    if (buffer[0] != 'y' && buffer[0] != 'Y') {
        printf("Deletion cancelled.\n");
        return;
    }

    // Free string fields
    free(list->records[index].date);
    free(list->records[index].category);
    free(list->records[index].description);

    // Shift elementi a sinistra
    for (int i = index; i < list->count - 1; i++) {
        list->records[i] = list->records[i + 1];
    }

    list->count--;
    printf("Expense ID %d deleted.\n", id);
}

