#include <unistd.h>

#include "lease.h"
#include "session.h"

void watcher_run(const char *lease_file)
{
    while (1) {

        session_init();          // sementara, reset lalu baca ulang

        lease_load(lease_file);

        session_dump();

        sleep(3);
    }
}