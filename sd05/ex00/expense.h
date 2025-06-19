#ifndef EXPENSE_H
# define EXPENSE_H

typedef struct s_expense
{
	char				*date;
	char				*category;
	char				*description;
	float				amount;
	struct s_expense	*next;
}	t_expense;

// Carica le spese da un file CSV
t_expense	*load_expenses(const char *filename);

// Stampa le spese in formato leggibile
void		print_expenses(const t_expense *head);

// Calcola il totale delle spese
float		total_expenses(const t_expense *head);

// Libera la lista delle spese
void		free_expenses(t_expense *head);

#endif
