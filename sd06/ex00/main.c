#include "library.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 256

void show_menu(void) {
    printf("\n====== Community Digital Library ======\n\n");
    printf("1. Visualizza tutti i libri\n");
    printf("2. Cerca per titolo\n");
    printf("3. Cerca per autore\n");
    printf("4. Mostra statistiche\n");
    printf("5. Esci\n");
    printf("\nScelta: ");
}

int main(void) {
    CatalogoLibri catalogo;
    const char *filename = "catalogue.csv";

    if (load_catalog(filename, &catalogo) != 0) {
        fprintf(stderr, "Errore nel caricamento del catalogo da '%s'\n", filename);
        return 1;
    }

    int scelta = 0;
    char input[MAX_INPUT];
    char query[MAX_INPUT];

    do {
        show_menu();
        read_input(input, MAX_INPUT);  // legge la scelta come stringa
        scelta = atoi(input);          // converte in intero

        switch (scelta) {
            case 1:
                print_all_books(&catalogo);
                break;
            case 2:
                printf("Inserisci parte del titolo: ");
                read_input(query, MAX_INPUT);
                search_by_title(&catalogo, query);
                break;
            case 3:
                printf("Inserisci parte del nome autore: ");
                read_input(query, MAX_INPUT);
                search_by_author(&catalogo, query);
                break;
            case 4:
                print_statistics(&catalogo);
                break;
            case 5:
                printf("\n👋 Uscita...\n");
                break;
            default:
                printf("⚠️ Scelta non valida. Inserisci un numero da 1 a 5.\n");
        }

    } while (scelta != 5);

    free_catalog(&catalogo);
    return 0;
}
