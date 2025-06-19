#include "critical_windows.h"

/// "Worker": conta quanti valori in una finestra di 5 giorni sono maggiori o uguali a una certa soglia.
/// Serve a verificare la prima condizione: almeno 3 giorni con valori >= 70.
static int count_days_above_threshold(const int *window, int threshold) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (window[i] >= threshold)
            count++;
    }
    return count;
}

/// "Worker": verifica se c'è almeno un valore nella finestra che supera un limite massimo.
/// Serve a controllare la seconda condizione: nessun valore > 150.
static int has_value_above_max(const int *window, int max_value) {
    for (int i = 0; i < 5; i++) {
        if (window[i] > max_value)
            return 1;
    }
    return 0;
}

/// "Worker": verifica se c'è almeno un valore nella finestra che supera un limite massimo.
/// Serve a controllare la seconda condizione: nessun valore > 150.
static int compute_average(const int *window) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += window[i];
    }
    return sum / 5;
}

/// "Decisore": determina se una finestra di 5 letture è "critica".
/// Si basa sulle 3 condizioni specificate nel problema.
/// (tutte le finestre possibili)
static int is_critical_window(const int *window) {
    if (count_days_above_threshold(window, 70) < 3)
        return 0;
    if (has_value_above_max(window, 150))
        return 0;
    if (compute_average(window) < 90)
        return 0;
    return 1;
}

/// "Supervisore" : analizza una serie di letture sismiche.
/// Scorre ogni sottosequenza di 5 giorni e conta quante sono "critiche".
int count_critical_windows(const int *readings, int size) {
    int count = 0;

    if (size < 5)
        return 0;

    for (int i = 0; i <= size - 5; i++) {
        if (is_critical_window(&readings[i]))
            count++;
    }

    return count;
}

/* 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 6) {
        // Servono almeno 5 valori per avere una finestra valida
        printf("Usage: %s <reading1> <reading2> ... (at least 5 readings)\n", argv[0]);
        return 1;
    }

    int size = argc - 1;
    int readings[size];

    for (int i = 0; i < size; i++) {
        readings[i] = atoi(argv[i + 1]);
    }

    int result = count_critical_windows(readings, size);
    printf("Critical windows: %d\n", result);

    return 0;
}
 */