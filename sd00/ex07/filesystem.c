#include "filesystem.h"
#include <stdlib.h>
#include <string.h>

FSNode *create_file(const char *name, int size) {
    FSNode *file = malloc(sizeof(FSNode));
    if (!file) 
        return NULL;
    file->name = strdup(name);
    file->size = size;
    file->child = NULL; /* per le folder se ne occuperà add_child(); */
    file->sibling = NULL;
    return file;
}

FSNode *create_folder(const char *name) {
    return create_file(name, 0); // stessa logica, ma size = 0
}

/* Appende alla fine della lista dei figli -> ordine delle chiamate a add_child(). */
void add_child(FSNode *parent, FSNode *child) {
    if (!parent || !child) return;
    if (!parent->child)
        parent->child = child;
    else {
        FSNode *current = parent->child;
        while (current->sibling)
            current = current->sibling;
        current->sibling = child;
    }
}

FSNode *get_children(const FSNode *parent) {
    return parent ? parent->child : NULL;
}

FSNode *get_sibling(const FSNode *node) {
    return node ? node->sibling : NULL;
}

