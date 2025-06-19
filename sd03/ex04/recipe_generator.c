#include "recipe_generator.h"
#include <stdlib.h>

/* Livello intermedio */
static struct Recipe *generate_approved_recipe(struct Ingredients *ingredients, struct TasteProfile *taste)
{
    struct Recipe *recipe = NULL;

    while (1)
    {
        recipe = create_recipe(ingredients, taste);
        if (!recipe)
            return NULL;

        if (get_user_approval(recipe))
            return recipe;

        free_recipe(recipe);
        recipe = NULL;
    }
}

/* Livello alto  */
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

    struct Recipe *final_recipe = generate_approved_recipe(ingredients, taste);

    free_ingredients(ingredients);
    free_taste_profile(taste);

    return final_recipe;
}
