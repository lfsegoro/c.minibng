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

int session_remove(
        const char *ip);

void session_dump(void);

void session_mark_all_unvisited(void);

void session_mark_visited(const char *ip);

void session_remove_unvisited(void);
#endif