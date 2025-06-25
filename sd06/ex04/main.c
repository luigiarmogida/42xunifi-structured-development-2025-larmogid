#include "expense_tracker.h"
#include "cleanup.h"
#include  <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s expenses.csv\n", argv[0]);
        return 1;
    }

    ExpenseList list;
    if (load_expenses_from_file(argv[1], &list) < 0)
        return 1;

    run_interactive_menu(&list);

    if (save_expenses_to_file(argv[1], &list) < 0)
        return 1;

    free_expense_list(&list); // <--- libera tutta la memoria allocata
    return 0;
}