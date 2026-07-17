#include <stdio.h>
#include <string.h>

#include "lease.h"
#include "session.h"

static int lease_parse_line(const char *line)
{
    char mac[18];
    char ip[16];
    char hostname[64];

    if (sscanf(line,
               "%*s %17s %15s %63s",
               mac,
               ip,
               hostname) != 3)
    {
        return -1;
    }

    subscriber_session_t *s;

s = session_find(ip);

if (s == NULL) {

    s = session_add(ip, mac, hostname);
}

if (s != NULL) {

    session_mark_visited(ip);
}

    return 0;
}

int lease_load(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return -1;

    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        lease_parse_line(line);
    }

    fclose(fp);

    return 0;
}