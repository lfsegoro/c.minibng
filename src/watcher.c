#include <unistd.h>

#include "lease.h"
#include "session.h"

void watcher_run(const char *lease_file)
{
    while (1) {

    session_mark_all_unvisited();

    lease_load(lease_file);

    session_remove_unvisited();

    session_dump();

    sleep(3);
    }
}