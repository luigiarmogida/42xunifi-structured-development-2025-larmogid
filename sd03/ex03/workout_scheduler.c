#include "workout_scheduler.h"
#include <stdlib.h>

static struct UserData *fetch_user_data(char *username)
{
	return get_user_data(username);
}

static struct WorkoutPlan *build_and_refine_plan(struct UserData *data)
{
	struct WorkoutPlan *plan = build_base_plan(data);
	if (!plan)
		return NULL;

	plan = refine_plan(plan, data);
	return plan;
}

static int schedule_days(struct WorkoutPlan *plan)
{
	int duration = determine_duration(plan);
	if (duration <= 0)
		return -1;

	for (int day = 0; day < duration; ++day)
	{
		assign_daily_exercises(plan, day);
		assign_daily_tips(plan, day);
	}
	return 0;
}

static void cleanup_user_data(struct UserData *data)
{
	if (data)
		free_user_data(data);
}

struct WorkoutPlan *create_workout_schedule(char *username)
{
	struct UserData *data = fetch_user_data(username);
	if (!data)
		return NULL;

	struct WorkoutPlan *plan = build_and_refine_plan(data);
	if (!plan)
	{
		cleanup_user_data(data);
		return NULL;
	}

	if (schedule_days(plan) < 0)
	{
		cleanup_user_data(data);
		free_workout_plan(plan);
		return NULL;
	}

	cleanup_user_data(data);
	return plan;
}
