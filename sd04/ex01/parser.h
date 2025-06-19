#ifndef PARSER_H
# define PARSER_H

# include "expense_tracker.h"

/*
** Carica le spese dal file specificato, riempiendo l'array records[].
** Ritorna il numero di record validi caricati.
*/
int     load_expenses(const char *filename, t_expense *records[]);

/*
** Parsea una singola linea del file in un record di spesa.
** Ritorna true se la linea è valida, false altrimenti.
*/
bool    parse_line(const char *line, t_expense **record);

/*
** Verifica e converte una stringa data in un oggetto t_date.
*/
bool    is_valid_date(const char *str, t_date *date_out);

/*
** Verifica e converte una stringa in un importo float valido.
*/
bool    is_valid_amount(const char *str, float *amount_out);

/*
** Rimuove spazi iniziali e finali da una stringa.
*/
char    *trim_whitespace(char *str);

/*
** Libera la memoria allocata per un record di spesa.
*/
void    free_expense(t_expense *record);

#endif
