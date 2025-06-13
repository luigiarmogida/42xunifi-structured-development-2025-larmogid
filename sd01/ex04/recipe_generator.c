#include "recipe_generator.h"
#include <stdlib.h>

struct Recipe *create_custom_recipe(void)
{
    struct Ingredients *ingredients = get_current_ingredients();
    if (!ingredients)
        return NULL;

    struct TasteProfile *taste = get_user_taste_profile();
    if (!taste)
    {
        free_ingredients(ingredients);
        return NULL;
    }

    struct Recipe *recipe = NULL;
    while (1)
    {
        recipe = create_recipe(ingredients, taste);
        if (!recipe)
            break;

        if (get_user_approval(recipe))
            break;

        free_recipe(recipe);
        recipe = NULL;
    }

    free_ingredients(ingredients);
    free_taste_profile(taste);
    return recipe;
}
