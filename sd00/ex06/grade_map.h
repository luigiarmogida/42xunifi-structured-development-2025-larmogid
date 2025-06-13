#ifndef GRADE_MAP_H
#define GRADE_MAP_H

// GradeMapper: tipo funzione che prende uno score e restituisce una stringa costante
typedef const char *(*GradeMapper)(int score);

// Mappa una lista di punteggi secondo una funzione di mapping
void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);

// Le 3 strategie disponibili
const char *plusminus_mapper(int score);
const char *passfail_mapper(int score);
const char *standard_mapper(int score);

#endif // GRADE_MAP_H
