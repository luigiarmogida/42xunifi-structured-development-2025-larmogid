#include <stdio.h>
#include "utils.h"

// strip_newline: implementa strcspn()
// Cerca il primo carattere '\n' e lo sostituisce con '\0'
// Utility I/O: read_input() rimuove newline dagli input dell’utente
// L'uso di `\n` in output resta responsabilità della formattazione nel chiamante
void strip_newline(char *s) {
    for (int i = 0; s[i]; ++i) {
        if (s[i] == '\n') {
            s[i] = '\0';
            break;
        }
    }
}

// read_input: lettura sicura da stdin con rimozione newline
void read_input(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        strip_newline(buffer);
    }
}
