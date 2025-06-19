/* 
Lo scheduling è il processo con cui l' OS decide quale processo o thread 

eseguire, e su quale CPU/core, e per quanto tempo.

Sistemi multicore (lo scheduling distribuisce i task su più core).

La funzione schedule_tasks() deve:

   1. Analizzare i task per carico e I/O              → profile_tasks

   2. Calcolare le priorità                           → compute_priorities_mock

   3. Ottenere il numero di core disponibili          → get_available_core_count

   4. Allocare la struttura del risultato             → create_schedule_result

   5. Assegnare iterativamente i task ai core         → select_best_task_for_current_priorities
                                                      → update_schedule_entry

   6. Gestire correttamente la memoria                → free_task_profile / free_priority_map

*/

#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <stdlib.h>

// Forward declarations delle strutture usate nei prototipi
struct TaskList; /* da schedulare */
struct TaskProfile; /* Profilazione: carico, I/O, comportamento */
struct PriorityMap; /* per ciascun task */
struct ScheduleResult;

// Coordina l'intero processo:
// 1. Profilazione dei task
// 2. Calcolo delle priorità
// 3. Assegnazione ai core
struct ScheduleResult *schedule_tasks(struct TaskList *tasks);

// Analizza il comportamento dei task (carico, I/O, ecc.) e produce una profilazione
// Restituisce un oggetto TaskProfile usato per calcolare le priorità
struct TaskProfile *profile_tasks(struct TaskList *tasks);

// Calcola la mappa delle priorità a partire dalla profilazione
// Ogni task riceve un valore di priorità schedulabile
struct PriorityMap *compute_priorities_mock(struct TaskProfile *profile);

// Core disponibili sulla CPU
int get_available_core_count(void);

// Seleziona il task migliore da assegnare ora, dato profilo e priorità correnti
int select_best_task_for_current_priorities(struct TaskProfile *profile, struct PriorityMap *priorities);

// Crea e inizializza la struttura per salvare il risultato finale della schedulazione
// (es. un array di task assegnati per ogni core)
struct ScheduleResult *create_schedule_result(int core_count);

// Aggiorna la struttura dei risultati assegnando un task a un core specifico
void update_schedule_entry(struct ScheduleResult *result, int core_id, int task_id);

// Funzioni di cleanup
void free_task_profile(struct TaskProfile *profile);
void free_priority_map(struct PriorityMap *priorities);

#endif // TASK_SCHEDULER_H
