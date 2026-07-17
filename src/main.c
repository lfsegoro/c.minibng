#include "watcher.h"
#include "session.h"
#include <unistd.h>

int main(void)
{
    session_init();

    watcher_start("sample.leases");

    while (1) {

        sleep(60);
    }

    return 0;
}