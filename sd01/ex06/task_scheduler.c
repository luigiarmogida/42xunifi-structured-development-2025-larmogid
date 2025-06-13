#include "task_scheduler.h"

// riceve una lista di task, calcola priorità e distribuisce i task sui core disponibili.
struct ScheduleResult *schedule_tasks(struct TaskList *tasks) {
    // 1. Analisi iniziale dei task per ottenere informazioni di carico e I/O
    struct TaskProfile *profile = profile_tasks(tasks);
    if (!profile)
        return NULL; /* profilazione fallita */

    // 2. Calcolo della mappa di priorità sulla base del profilo ottenuto
    struct PriorityMap *priorities = compute_priorities_mock(profile);
    if (!priorities) {
        free_task_profile(profile);
        return NULL;
    }

    // 3. Recupero del numero di core disponibili nel sistema
    int core_count = get_available_core_count();

    // 4. Allocazione della struttura che conterrà l'output della schedulazione
    struct ScheduleResult *result = create_schedule_result(core_count);
    if (!result) { // Se fallisce l’allocazione:
        free_priority_map(priorities);
        free_task_profile(profile);
        return NULL;
    }

    // 5. Assegnazione dei task ai core, uno per volta
    for (int i = 0; i < core_count; ++i) {
        // Seleziona il miglior task da eseguire ora secondo profilo + priorità
        int task_id = select_best_task_for_current_priorities(profile, priorities);
        if (task_id == -1)
            break; // Non ci sono più task disponibili da assegnare

        // Registra l'assegnazione del task al core corrente
        update_schedule_entry(result, i, task_id);
    }

    // 6. Cleanup delle strutture temporanee usate nella schedulazione
    free_priority_map(priorities);
    free_task_profile(profile);
    return result;
}

/* 
// === Main di test ===
#include <stdio.h>

// Mock structures
struct TaskList { int dummy; };
struct TaskProfile { int dummy; };
struct PriorityMap { int dummy; };
struct ScheduleResult { int core_count; };

// Mock implementations
struct TaskProfile *profile_tasks(struct TaskList *tasks) {
    (void)tasks;
    return malloc(sizeof(struct TaskProfile));
}

struct PriorityMap *compute_priorities_mock(struct TaskProfile *profile) {
    (void)profile;
    return malloc(sizeof(struct PriorityMap));
}

int get_available_core_count(void) {
    return 4;
}

int select_best_task_for_current_priorities(struct TaskProfile *profile, struct PriorityMap *priorities) {
    static int id = 0;
    (void)profile; (void)priorities;
    if (id >= 4)
        return -1;
    return id++;
}

struct ScheduleResult *create_schedule_result(int core_count) {
    struct ScheduleResult *res = malloc(sizeof(struct ScheduleResult));
    if (!res)
        return NULL;
    res->core_count = core_count;
    return res;
}

void update_schedule_entry(struct ScheduleResult *result, int core_id, int task_id) {
    printf("Assigned task %d to core %d\n", task_id, core_id);
    (void)result;
}

void free_task_profile(struct TaskProfile *profile) {
    free(profile);
}

void free_priority_map(struct PriorityMap *priorities) {
    free(priorities);
}

int main(void) {
    struct TaskList tasks;
    struct ScheduleResult *result = schedule_tasks(&tasks);

    if (result) {
        printf("Scheduling complete on %d cores.\n", result->core_count);
        free(result);
    } else {
        printf("Scheduling failed.\n");
    }

    return 0;
}
 */