/* 
Strategia step-by-step:

1. analyze_user_mood() → restituisce MoodSettings* o NULL

2. default_filters() → restituisce FilterSettings* o NULL

3. get_mood_variations() → per sapere quante volte raffinare i filtri

4. Raffinare i filtri (usare refine_filters() in un ciclo n volte)

5. Se filters_require_popular_song() è vero → fetch_popular_song(), altrimenti fetch_niche_song()

6. combine_with_mood_playlist() → restituisce Playlist*

7. In caso di errore, liberare tutta la memoria già allocata 
*/

#ifndef PLAYLIST_CREATOR_H
#define PLAYLIST_CREATOR_H

// Forward declaration delle strutture, visto che non le implementiamo
struct MoodSettings;
struct FilterSettings;
struct SongData;
struct Playlist;

// Funzione principale da implementare in playlist_creator.c
struct Playlist *create_playlist(void);

// Funzioni esterne dichiarate come disponibili
struct MoodSettings *analyze_user_mood(void);
struct FilterSettings *default_filters(void);
int get_mood_variations(struct MoodSettings *mood);
struct FilterSettings *refine_filters(struct FilterSettings *current);
int filters_require_popular_song(struct FilterSettings *filters);
struct SongData *fetch_popular_song(void);
struct SongData *fetch_niche_song(void);
struct Playlist *combine_with_mood_playlist(struct SongData *song, struct MoodSettings *mood);

// Free functions
void free_mood_settings(struct MoodSettings *mood);
void free_filter_settings(struct FilterSettings *filters);
void free_song_data(struct SongData *song);
void free_playlist(struct Playlist *playlist);

#endif // PLAYLIST_CREATOR_H
