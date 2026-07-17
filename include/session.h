#ifndef SESSION_H
#define SESSION_H

#include "types.h"



void session_init(void);

subscriber_session_t *session_add(
        const char *ip,
        const char *mac,
        const char *hostname);

subscriber_session_t *session_find(
        const char *ip);

typedef void (*session_callback_t)(subscriber_session_t *);

void session_foreach(session_callback_t callback);

int session_remove(
        const char *ip);

void session_dump(void);

void session_mark_all_unvisited(void);

void session_mark_visited(const char *ip);

void session_remove_unvisited(void);


#endif