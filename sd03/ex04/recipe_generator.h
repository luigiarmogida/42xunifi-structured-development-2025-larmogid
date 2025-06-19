/* 
Recipe Generator - Flow Control Summary

Controllo del flusso logico nella funzione create_custom_recipe()

Obiettivo:

- ottenere gli ingredienti attuali dal frigo,

- ottenere il profilo gustativo dell’utente,

- generare ripetutamente una ricetta finché l’utente non approva,

- pulire correttamente la memoria in caso di errore o ricette non approvate,

- restituire la ricetta approvata.
 */

#ifndef RECIPE_GENERATOR_H
# define RECIPE_GENERATOR_H

struct Ingredients;
struct TasteProfile;
struct Recipe;

struct Ingredients *get_current_ingredients(void);
struct TasteProfile *get_user_taste_profile(void);
struct Recipe *create_recipe(struct Ingredients *ingredients, struct TasteProfile *taste);
int get_user_approval(struct Recipe *recipe);
void free_ingredients(struct Ingredients *ing);
void free_taste_profile(struct TasteProfile *tp);
void free_recipe(struct Recipe *recipe);

struct Recipe *create_custom_recipe(void);

#endif
