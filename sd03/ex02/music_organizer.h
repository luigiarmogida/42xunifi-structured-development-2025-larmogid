#ifndef MUSIC_ORGANIZER_H
#define MUSIC_ORGANIZER_H

struct MusicLibrary;
struct MusicFile;

struct MusicLibrary *create_music_library(void);
const char **scan_directory(const char *directory_path);
struct MusicFile *process_music_file(const char *directory_path, const char *filename);
void update_music_library(struct MusicLibrary *library, struct MusicFile *song);

struct MusicLibrary *organize_music_library(const char *directory_path);

#endif
