#ifndef WORKOUT_SCHEDULER_H
#define WORKOUT_SCHEDULER_H

/* Passaggi da eseguire in ordine:

1. - get_user_data(username) → Ottieni i dati utente.

2. - build_base_plan(data) → Crea un piano di base.

3. - refine_plan(plan, data) → (Opzionale) Raffina il piano.

4. - determine_duration(plan) → Quanti giorni deve durare.

5. - Per ogni giorno:

    - assign_daily_exercises(plan, giorno)

    - assign_daily_tips(plan, giorno)

6. - Ritorna il piano finale.

⚠️ Se qualcosa fallisce, bisogna:

    Fare free_* opportunamente.

    Restituire NULL. */

// Strutture dati forward-declared 
struct UserData;
struct WorkoutPlan;

// Funzione principale da implementare
struct WorkoutPlan *create_workout_schedule(char *username);

// Funzioni fornite (mock)
struct UserData *get_user_data(char *username);
struct WorkoutPlan *build_base_plan(struct UserData *data);
struct WorkoutPlan *refine_plan(struct WorkoutPlan *plan, struct UserData *data);
int determine_duration(struct WorkoutPlan *plan);
void assign_daily_exercises(struct WorkoutPlan *plan, int day);
void assign_daily_tips(struct WorkoutPlan *plan, int day);
void free_user_data(struct UserData *data);
void free_workout_plan(struct WorkoutPlan *plan);

#endif // WORKOUT_SCHEDULER_H
