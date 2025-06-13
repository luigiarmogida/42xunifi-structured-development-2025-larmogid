#include "music_organizer.h"
#include <stdlib.h>

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

    for (int i = 0; filenames[i]; i++) {
        struct MusicFile *song = process_music_file(directory_path, filenames[i]);
        if (!song)
            continue; // skip file if processing failed

        /* Non libera MusicFile dopo update_music_library() 
        perché si presume venga "preso in carico" dalla libreria. */
        update_music_library(library, song);
    }

    /* Libera memoria solo dove necessario (filenames). */
    for (int i = 0; filenames[i]; i++)
        free((void *)filenames[i]);
    free((void *)filenames);

    return library;
}
