#ifndef GRADE_MAP_H
# define GRADE_MAP_H

typedef struct GradeNode {
    char grade[16];
    int count;
    struct GradeNode *next;
} GradeNode;

typedef const char *(*GradeMapper)(int score);

// 🔽 Livello basso: mapper specifici (chi "traduce")
const char *plusminus_mapper(int score);
const char *standard_mapper(int score);
const char *passfail_mapper(int score);

// 🔼 Livello medio: coordinatore che invoca il mapper
void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);

// Livello alto: gestione distribuzione
GradeNode *compute_distribution(const char **mapped_grades, int size);
void print_distribution(GradeNode *head);
void free_distribution(GradeNode *head);

#endif
