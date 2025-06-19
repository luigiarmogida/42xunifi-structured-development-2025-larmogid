#include "task_scheduler.h"

// Assegna i task ai core disponibili, uno per volta
static void assign_tasks_to_cores(struct ScheduleResult *result,
                                  struct TaskProfile *profile,
                                  struct PriorityMap *priorities,
                                  int core_count) {
    for (int core_id = 0; core_id < core_count; ++core_id) {
        int task_id = select_best_task_for_current_priorities(profile, priorities);
        if (task_id == -1)
            break;
        update_schedule_entry(result, core_id, task_id);
    }
}

// Libera le strutture temporanee usate durante la schedulazione
static void release_temp_resources(struct TaskProfile *profile,
                                   struct PriorityMap *priorities) {
    free_priority_map(priorities);
    free_task_profile(profile);
}

// Funzione principale: organizza il flusso completo di scheduling
struct ScheduleResult *schedule_tasks(struct TaskList *tasks) {
    // 1. Analizza il carico e I/O dei task
    struct TaskProfile *profile = profile_tasks(tasks);
    if (!profile)
        return NULL;

    // 2. Calcola la priorità dei task
    struct PriorityMap *priorities = compute_priorities_mock(profile);
    if (!priorities) {
        free_task_profile(profile);
        return NULL;
    }

    // 3. Determina il numero di core disponibili
    int core_count = get_available_core_count();

    // 4. Alloca la struttura per il risultato finale
    struct ScheduleResult *result = create_schedule_result(core_count);
    if (!result) {
        release_temp_resources(profile, priorities);
        return NULL;
    }

    // 5. Assegna i task ai core
    assign_tasks_to_cores(result, profile, priorities, core_count);

    // 6. Cleanup
    release_temp_resources(profile, priorities);

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