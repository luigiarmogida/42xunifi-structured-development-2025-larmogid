#ifndef FILESYSTEM_H
#define FILESYSTEM_H

typedef struct FSNode {
    char *name;
    int size; 
    /* i "next" personalizzati del tuo albero: */
    struct FSNode *child;   // "dentro"  (primo contenuto)
    struct FSNode *sibling; // "accanto" (elementi dello stesso livello, tipo lista).
} FSNode;

// Funzioni di alto livello (interfaccia pubblica)
FSNode *create_file(const char *name, int size);
FSNode *create_folder(const char *name);
void add_child(FSNode *parent, FSNode *child); /* aggiungi in coda */

// Accessori basso livello
FSNode *get_children(const FSNode *parent);
FSNode *get_sibling(const FSNode *node);

// Bonus
int compute_total_size(const FSNode *node);
void print_structure(const FSNode *node, int indent);
void free_filesystem(FSNode *node);

#endif