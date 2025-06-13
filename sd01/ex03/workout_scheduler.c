#include "workout_scheduler.h"
#include <stdlib.h>

struct WorkoutPlan *create_workout_schedule(char *username)
{
	struct UserData *data = get_user_data(username);
	if (!data)
		return NULL;

	struct WorkoutPlan *plan = build_base_plan(data);
	if (!plan)
	{
		free_user_data(data);
		return NULL;
	}

	plan = refine_plan(plan, data);
	if (!plan)
	{
		free_user_data(data);
		return NULL;
	}

	int duration = determine_duration(plan);
	if (duration <= 0)
	{
		free_user_data(data);
		free_workout_plan(plan);
		return NULL;
	}

	for (int day = 0; day < duration; ++day)
	{
		assign_daily_exercises(plan, day);
		assign_daily_tips(plan, day);
	}

	free_user_data(data);
	return plan;
}
