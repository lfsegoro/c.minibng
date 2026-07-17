#include <pthread.h>
#include <unistd.h>

#include "lease.h"
#include "policy.h"
#include "session.h"

static const char *gLeaseFile;

static void *watcher_thread(void *arg)
{
    (void)arg;

    while (1) {

        session_mark_all_unvisited();

        lease_load(gLeaseFile);

        session_remove_unvisited();

        session_foreach(policy_apply);

        session_dump();

        sleep(3);
    }

    return NULL;
}

void watcher_start(const char *lease_file)
{
    pthread_t tid;

    gLeaseFile = lease_file;

    pthread_create(&tid,
                   NULL,
                   watcher_thread,
                   NULL);

    pthread_detach(tid);
}