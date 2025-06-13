#include "playlist_creator.h"
#include <stdlib.h>

struct Playlist *create_playlist(void) {
    struct MoodSettings *mood = NULL;
    struct FilterSettings *filters = NULL;
    struct SongData *song = NULL;
    struct Playlist *playlist = NULL;

    // Step 1: Analisi umore utente
    mood = analyze_user_mood(); /* alloco mood */
    if (!mood)
        return NULL;

    // Step 2: Costruzione filtri di default
    filters = default_filters();
    if (!filters) {
        free_mood_settings(mood); /* cleanup */
        return NULL;
    }
    // Step 3: Calcolo variazioni d'umore
    int variations = get_mood_variations(mood);

    // Step 4: Per ogni variazione, raffina iterativamente i filtri finché non sono stabili
    /* "Refine filters according to mood variations".
       Peró la funzione di refine non prende in input mood 
       né il ritorno di get_mood_variations... */
    for (int i = 0; i < variations; ++i) {
        while (1) {
            struct FilterSettings *refined = refine_filters(filters);
            if (!refined) {
                free_mood_settings(mood);
                free_filter_settings(filters);
                return NULL;
            }
            /* Se refined == filters, vuol dire che non ci sono più modifiche 
            da fare per quella variazione. */
            if (refined == filters)
                break; // stabile: non raffino più

            free_filter_settings(filters);
            filters = refined;
        }
    }

    // Step 5: Scelta della canzone (popolare o di nicchia)
    if (filters_require_popular_song(filters))
        song = fetch_popular_song();
    else
        song = fetch_niche_song(); /* fallback */

    if (!song) {
        free_mood_settings(mood);
        free_filter_settings(filters);
        return NULL;
    }

    // Step 6: Combinazione della canzone con l'umore
    playlist = combine_with_mood_playlist(song, mood);

    // Step 7: Cleanup risorse intermedie
    free_mood_settings(mood);
    free_filter_settings(filters);
    free_song_data(song);

    return playlist; // può essere NULL se combinazione fallisce
}
