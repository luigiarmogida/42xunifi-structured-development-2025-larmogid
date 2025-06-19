/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:39:51 by luigi             #+#    #+#             */
/*   Updated: 2025/06/16 22:32:26 by luigi            ###   ########.fr       */
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

/* Funzione atomica: crea nodo generico */
static FSNode *create_node(const char *name, int size) {
    FSNode *node = malloc(sizeof(FSNode));
    if (!node) return NULL;
    node->name = strdup(name);
    node->size = size;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

/* Alto livello */
FSNode *create_file(const char *name, int size) {
    return create_node(name, size);
}

/* Alto livello */
FSNode *create_folder(const char *name) {
    return create_file(name, 0); // stessa logica, ma size = 0
}

/* Appende in fondo alla lista dei figli -> ordine delle chiamate a add_child(). */
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

/* Livello basso */
FSNode *get_children(const FSNode *parent) {
    return parent ? parent->child : NULL;
}

FSNode *get_sibling(const FSNode *node) {
    return node ? node->sibling : NULL;
}


#include <stdio.h>
#include <stdlib.h>

void print_structure(const FSNode *node, int depth) {
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

/* 
static void build_sample_fs(FSNode **root, const char *filename, int size) {
    *root = create_folder("root");
    FSNode *docs = create_folder("documents");
    FSNode *file = create_file(filename, size);

    add_child(*root, docs);
    add_child(docs, file);
}

int main(int argc, char **argv) {
    // 1. Input
    const char *filename = "default.txt";
    int size = 10;

    if (argc == 3) {
        filename = argv[1];
        size = atoi(argv[2]);
    } else {
        printf("No arguments provided. Using default file: %s (%d KB).\n", filename, size);
    }

    // 2. Costruzione
    FSNode *root = NULL;
    build_sample_fs(&root, filename, size);

    // 3. Visualizzazione
    print_structure(root, 0);

    // 4. Pulizia
    free_fs(root);

    return 0;
} 
*/