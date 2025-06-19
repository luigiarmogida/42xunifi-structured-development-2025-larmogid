#include "music_organizer.h"
#include <stdlib.h>
#include "music_organizer.h"
#include <stdlib.h>

/* Livello: Basso (operativo) */
static void load_single_music_file(struct MusicLibrary *library, const char *directory_path, const char *filename)
{
    struct MusicFile *song = process_music_file(directory_path, filename);
    if (song)
        update_music_library(library, song);
}

/* Livello: Medio (coordinazione locale) */
static void load_all_music_files(struct MusicLibrary *library, const char *directory_path, const char **filenames)
{
    for (int i = 0; filenames[i]; i++)
        load_single_music_file(library, directory_path, filenames[i]);
}

/* Livello: Basso (operativo) */
static void free_filenames(const char **filenames)
{
    for (int i = 0; filenames[i]; i++)
        free((void *)filenames[i]);
    free((void *)filenames);
}

/* Livello: Alto (controllo/gestione) */
struct MusicLibrary *organize_music_library(const char *directory_path)
{
    struct MusicLibrary *library = create_music_library();
    if (!library)
        return NULL;

    const char **filenames = scan_directory(directory_path);
    if (!filenames) {
        free(library);
        return NULL;
    }

    load_all_music_files(library, directory_path, filenames);
    free_filenames(filenames);

    return library;
}
