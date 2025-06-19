#include "playlist_creator.h"
#include <stdlib.h>

// --- LIVELLO BASSO: Funzioni helper per sotto-compiti concreti --- //

/* Crea le impostazioni iniziali dell'umore utente */
static struct MoodSettings *init_mood_settings(void) {
    return analyze_user_mood(); // può restituire NULL
}

/* Crea le impostazioni filtro di default */
static struct FilterSettings *init_filter_settings(void) {
    return default_filters(); // può restituire NULL
}

/* Applica le variazioni d'umore ai filtri, raffinandoli */
static struct FilterSettings *apply_mood_variations(
    struct FilterSettings *filters,
    int variations
) {
    for (int i = 0; i < variations; ++i) {
        while (1) {
            struct FilterSettings *refined = refine_filters(filters);
            if (!refined) return NULL;

            if (refined == filters) // Nessun cambiamento: stabile
                break;

            free_filter_settings(filters);
            filters = refined;
        }
    }
    return filters;
}

/* In base ai filtri, seleziona una canzone adatta */
static struct SongData *select_song(struct FilterSettings *filters) {
    if (filters_require_popular_song(filters))
        return fetch_popular_song();
    else
        return fetch_niche_song();
}

/* Pulizia generale in caso di errore intermedio */
static void cleanup_partial(
    struct MoodSettings *mood,
    struct FilterSettings *filters,
    struct SongData *song
) {
    if (mood) free_mood_settings(mood);
    if (filters) free_filter_settings(filters);
    if (song) free_song_data(song);
}

// --- LIVELLO ALTO: Coordinazione del flusso principale --- //

struct Playlist *create_playlist(void) {
    struct MoodSettings *mood = NULL;
    struct FilterSettings *filters = NULL;
    struct SongData *song = NULL;
    struct Playlist *playlist = NULL;

    // 1. Analizza l'umore dell'utente
    mood = init_mood_settings();
    if (!mood)
        return NULL;

    // 2. Ottieni i filtri di default
    filters = init_filter_settings();
    if (!filters) {
        free_mood_settings(mood);
        return NULL;
    }

    // 3. Ottieni il numero di variazioni d'umore da considerare
    int variations = get_mood_variations(mood);

    // 4. Applica le variazioni per raffinare i filtri
    struct FilterSettings *refined_filters = apply_mood_variations(filters, variations);
    if (!refined_filters) {
        cleanup_partial(mood, filters, NULL);
        return NULL;
    }
    filters = refined_filters;

    // 5. Seleziona una canzone in base ai filtri
    song = select_song(filters);
    if (!song) {
        cleanup_partial(mood, filters, NULL);
        return NULL;
    }

    // 6. Combina la canzone selezionata con l'umore per creare la playlist
    playlist = combine_with_mood_playlist(song, mood);

    // 7. Pulizia delle strutture intermedie
    cleanup_partial(mood, filters, song);

    // 8. Ritorna la playlist finale (può essere NULL se combinazione fallita)
    return playlist;
}

