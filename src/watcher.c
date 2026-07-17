#include <unistd.h>

#include "lease.h"
#include "session.h"
#include "policy.h"

void watcher_run(const char *lease_file)
{
    while (1) {

    session_mark_all_unvisited();

    lease_load(lease_file);

    session_remove_unvisited();

    session_foreach(policy_apply);

    session_dump();

    sleep(3);
    }
}