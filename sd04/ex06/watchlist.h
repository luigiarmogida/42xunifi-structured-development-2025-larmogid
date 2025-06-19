#ifndef WATCHLIST_H
#define WATCHLIST_H

typedef enum {
    MEDIA_MOVIE,
    MEDIA_TV,
    MEDIA_ANIME
} MediaType;

typedef struct s_viewing {
    int season;      // solo per TV/Anime
    int episode;     // solo per TV/Anime
    char *date;      // "YYYY-MM-DD"
    int rating;      // 1..10
    struct s_viewing *next;
} Viewing;

typedef struct s_media {
    int id;
    MediaType type;
    char *title;
    char *genre;
    Viewing *history;
    struct s_media *next;
} MediaItem;

typedef struct {
    MediaItem *head;
    int count;
} MediaList;

// logging per righe malformate durante il parsing
void log_warning(const char *message, const char *line);

#endif