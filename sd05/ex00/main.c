#include "expense.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
    if (argc != 2) {
      printf("Usage: %s expenses.csv\n", argv[0]);
      return 1;
    }
    t_expense *head = load_expenses(argv[1]);
    if (!head) {
      printf("No expenses found or error.\n");
      return 1;
    }
    print_expenses(head);
    printf("TOTAL: %.2f\n", total_expenses(head));
    free_expenses(head);
    return 0;
}
