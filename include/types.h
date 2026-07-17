#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef enum {
    CLIENT_BLOCKED,
    CLIENT_ACTIVE,
    CLIENT_ISOLATED,
    STATUS_BLOCKED = 0,
    STATUS_ACTIVE,
    STATUS_ISOLATED
} client_status_t;

typedef struct {
    char ip[16];
    char mac[18];
    char hostname[64];

    client_status_t status;

    uint64_t upload;
    uint64_t download;
    uint64_t limit;
} subscriber_session_t;


#endif