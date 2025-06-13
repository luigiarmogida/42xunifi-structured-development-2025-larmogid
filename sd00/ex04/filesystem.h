#ifndef FILESYSTEM_H
#define FILESYSTEM_H

/* 

| Tipo logico | Campo `size` | Campo `child`               | Semantica                     |
| ----------- | ------------ | --------------------------- | ----------------------------- |
| Cartella    | `0`          | `!= NULL` (se ha contenuto) | Può contenere altri `FSNode`  | -> può avere child 
| File        | `> 0`        | `NULL`                      | Non ha figli, solo dimensione |

root
├── docs
│   └── file1
└── img
    └── file2

MODELLO "first-child / next-sibling". 

Internamente è rappresentato così:

add_child(root, docs);
root
 └── child -> docs
               └── sibling -> img (docs e img entrambi figli diretti di root) 

create_file(name, size);
docs
 └── child -> file1
img
 └── child -> file2

*/

/*  
    Nessun array. Ogni nodo punta a uno solo:
    -figlio (inizio della lista dei figli),
    -fratello (prossimo figlio del genitore). 
*/
typedef struct FSNode {
    char *name;
    int size; 
    /* i "next" personalizzati del tuo albero: */
    struct FSNode *child;   // "dentro"  (primo contenuto)
    struct FSNode *sibling; // "accanto" (elementi dello stesso livello, tipo lista).
} FSNode;

FSNode *create_file(const char *name, int size);
FSNode *create_folder(const char *name);
void add_child(FSNode *parent, FSNode *child); /* in coda */
FSNode *get_children(const FSNode *parent);
FSNode *get_sibling(const FSNode *node);

#endif