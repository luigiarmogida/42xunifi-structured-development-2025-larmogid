#ifndef MEDIA_OPS_H
#define MEDIA_OPS_H

#include "watchlist.h"

// Aggiunge un nuovo media item con storia vuota
int add_media_item(MediaList *list, MediaType type, const char *title, const char *genre);

// Elimina un media item per ID (ritorna 1 se trovato e rimosso, 0 altrimenti)
int delete_media_item(MediaList *list, int id);

// Modifica titolo e genere di un media item
int edit_media_item(MediaItem *item, const char *new_title, const char *new_genre);

// Ricerca per ID
MediaItem *find_media_by_id(MediaList *list, int id);

#endif