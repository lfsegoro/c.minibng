#include <stdio.h>
#include <string.h>

#include "config.h"
#include "session.h"

typedef struct {
    int used;
    int visited;
    subscriber_session_t session;
} session_slot_t;

static session_slot_t table[MAX_SESSION];

void session_init(void)
{
    memset(table, 0, sizeof(table));
}

subscriber_session_t *session_find(const char *ip)
{
    for (int i = 0; i < MAX_SESSION; i++) {
        if (!table[i].used)
            continue;

        if (strcmp(table[i].session.ip, ip) == 0)
            return &table[i].session;
    }

    return NULL;
}

subscriber_session_t *session_add(
    const char *ip,
    const char *mac,
    const char *hostname)
{
    /* Sudah ada? */
    subscriber_session_t *s = session_find(ip);
    if (s)
        return s;

    /* Cari slot kosong */
    for (int i = 0; i < MAX_SESSION; i++) {

        if (table[i].used)
            continue;

        table[i].used = 1;

        memset(&table[i].session, 0, sizeof(subscriber_session_t));

        strncpy(table[i].session.ip, ip,
                sizeof(table[i].session.ip) - 1);

        strncpy(table[i].session.mac, mac,
                sizeof(table[i].session.mac) - 1);

        strncpy(table[i].session.hostname, hostname,
                sizeof(table[i].session.hostname) - 1);

        table[i].session.status = CLIENT_BLOCKED;

        return &table[i].session;
    }

    return NULL;    /* Table penuh */
}

int session_remove(const char *ip)
{
    for (int i = 0; i < MAX_SESSION; i++) {

        if (!table[i].used)
            continue;

        if (strcmp(table[i].session.ip, ip) == 0) {

            memset(&table[i], 0, sizeof(session_slot_t));

            return 0;
        }
    }

    return -1;
}

void session_mark_all_unvisited(void)
{
    for (int i = 0; i < MAX_SESSION; i++) {

        if (!table[i].used)
            continue;

        table[i].visited = 0;
    }
}

void session_mark_visited(const char *ip)
{
    for (int i = 0; i < MAX_SESSION; i++) {

        if (!table[i].used)
            continue;

        if (strcmp(table[i].session.ip, ip) == 0) {
            table[i].visited = 1;
            return;
        }
    }
}

void session_remove_unvisited(void)
{
    for (int i = 0; i < MAX_SESSION; i++) {

        if (!table[i].used)
            continue;

        if (table[i].visited)
            continue;

        memset(&table[i], 0, sizeof(session_slot_t));
    }
}


void session_dump(void)
{
    printf("\n===== SESSION TABLE =====\n");

    for (int i = 0; i < MAX_SESSION; i++) {

        if (!table[i].used)
            continue;

        subscriber_session_t *s = &table[i].session;

        printf("%-15s %-17s %-20s status=%d\n",
               s->ip,
               s->mac,
               s->hostname,
               s->status);
    }

    printf("=========================\n");
}