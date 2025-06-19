#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * ALTO LIVELLO:
 * calcola ricorsivamente la dimensione totale di una cartella,
 * sommando la dimensione di tutti i file e contenuti nidificati.
 */
int compute_total_size(const FSNode *node) {
    if (!node)
        return 0;
    
    int total = node->size;

    // Se è una cartella con figli, somma ricorsivamente
    const FSNode *child = node->child;
    while (child) {
        total += compute_total_size(child);
        child = child->sibling;
    }

    return total;
}

/*
 * ALTO LIVELLO:
 * stampa la struttura del filesystem in forma ad albero.
 * Usa indentazione per indicare la profondità.
 */
void print_structure(const FSNode *node, int indent) {
    while (node) {
        // Stampa indentazione
        for (int i = 0; i < indent; i++)
            printf("  ");

        printf("- %s", node->name);
        if (!node->child) // se non ha figli, è un file
            printf(" (%d)", node->size);
        printf("\n");

        // Stampa figli con indentazione aumentata
        if (node->child)
            print_structure(node->child, indent + 1);

        node = node->sibling;
    }
}

/*
 * ALTO LIVELLO:
 * libera ricorsivamente tutta la memoria allocata
 * per il filesystem.
 */
void free_filesystem(FSNode *node) {
    if (!node)
        return;

    // Libera tutti i figli
    free_filesystem(node->child);

    // Libera i fratelli
    free_filesystem(node->sibling);

    // Libera il nodo stesso
    free(node->name);
    free(node);
}

/* 
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FSNode *root = create_folder("root");
    FSNode *docs = create_folder("docs");
    FSNode *img = create_folder("images");
    FSNode *file1 = create_file("resume.pdf", 100);
    FSNode *file2 = create_file("photo.jpg", 200);

    add_child(docs, file1);
    add_child(img, file2);
    add_child(root, docs);
    add_child(root, img);

    print_structure(root, 0);
    printf("Total size: %d\n", compute_total_size(root));

    free_filesystem(root);
    return 0;
}
*/