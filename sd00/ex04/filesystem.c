/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:39:51 by luigi             #+#    #+#             */
/*   Updated: 2025/06/11 22:52:07 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                             
                                FILESYSTEM STRUCTURE                           
                                                                               
    Ogni nodo (FSNode) può rappresentare un file o una cartella.               
                                                                               
    MODELLO: FIRST-CHILD / NEXT-SIBLING                                        
                                                                               
    ┌────────────┐          ┌────────────┐         ┌────────────┐              
    │   folder   │ ───────► │   file1    │ ───────►│   file2    │ ───► NULL    
    └────────────┘          └────────────┘         └────────────┘              
            │                         │                       │                
        child = file1          sibling = file2         sibling = NULL          
                                                                               
    Ogni nodo punta a:                                                         
        - il suo primo figlio (child)                                          
        - il fratello successivo (sibling)                                     
                                                                             */

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


#include <stdio.h>
#include <stdlib.h>

void print_structure(FSNode *node, int depth) {
    while (node) {
        for (int i = 0; i < depth; ++i)
            printf("  ");
        printf("- %s (%s, %d KB)\n", node->name,
               node->size == 0 ? "folder" : "file", node->size);
        if (node->child)
            print_structure(node->child, depth + 1);
        node = node->sibling;
    }
}

void free_fs(FSNode *node) {
    if (!node) return;

    // Libera prima figli e fratelli
    free_fs(node->child);
    free_fs(node->sibling);

    // Libera il nome (strdup)
    free(node->name);

    // Libera il nodo stesso
    free(node);
}

/* int main(int argc, char **argv) {
    const char *filename = "default.txt";
    int size = 10;

    if (argc == 3) {
        filename = argv[1];
        size = atoi(argv[2]);
    } else {
        printf("No arguments provided. Using default file: %s (%d KB).\n", filename, size);
    }

    FSNode *root = create_folder("root");
    FSNode *docs = create_folder("documents");
    FSNode *file = create_file(filename, size);
    add_child(root, docs);
    add_child(docs, file);

    print_structure(root, 0);
    free_fs(root);

    return 0;
}
 */