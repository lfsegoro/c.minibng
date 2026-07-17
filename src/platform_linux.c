#include <stdio.h>

#include "platform.h"

void platform_allow(const char *ip)
{
    printf("[PLATFORM] ALLOW %s\n", ip);
}

void platform_block(const char *ip)
{
    printf("[PLATFORM] BLOCK %s\n", ip);
}