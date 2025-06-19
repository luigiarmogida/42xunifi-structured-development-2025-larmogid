#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "grade_map.h"

// 🔽 Livello basso: crea nuovo nodo con count 1
GradeNode *create_node(const char *grade) {
    GradeNode *node = malloc(sizeof(GradeNode));
    if (!node)
        return NULL;
    strncpy(node->grade, grade, 15);
    node->grade[15] = '\0';
    node->count = 1;
    node->next = NULL;
    return node;
}

// 🔽 Livello basso: cerca un nodo esistente
GradeNode *find_node(GradeNode *head, const char *grade) {
    while (head) {
        if (strcmp(head->grade, grade) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// 🔼 Livello alto: costruisce la distribuzione
GradeNode *compute_distribution(const char **mapped_grades, int size) {
    GradeNode *head = NULL;
    for (int i = 0; i < size; i++) {
        const char *grade = mapped_grades[i];
        GradeNode *existing = find_node(head, grade);
        if (existing) {
            existing->count++;
        } else {
            GradeNode *new_node = create_node(grade);
            if (!new_node)
                return NULL;
            new_node->next = head;
            head = new_node;
        }
    }
    return head;
}

// 🔽 Livello medio: output leggibile
void print_distribution(GradeNode *head) {
    while (head) {
        printf("%s: %d\n", head->grade, head->count);
        head = head->next;
    }
}

// 🔽 Livello basso: cleanup memoria
void free_distribution(GradeNode *head) {
    while (head) {
        GradeNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}

/* #include <stdio.h>
int main(void) {
    int scores[] = {98, 94, 89, 70, 50, 89, 70, 98};
    int size = sizeof(scores) / sizeof(scores[0]);
    const char *mapped_grades[size];

    // Mappa i voti
    map_scores(scores, size, plusminus_mapper, mapped_grades);
    for (int i = 0; i < size; i++) {
        printf("Score: %d -> Grade: %s\n", scores[i], mapped_grades[i]);
    }

    // Calcola distribuzione
    GradeNode *distribution = compute_distribution(mapped_grades, size);
    printf("\nGrade Distribution:\n");
    print_distribution(distribution);

    // Libera memoria
    free_distribution(distribution);

    return 0;
}
 */