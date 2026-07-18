#include "watcher.h"
#include "session.h"
#include <unistd.h>
#include "http.h"

int main(void)
{
    session_init();

    watcher_start("sample.leases");

    http_start(8080);

    while (1)
        sleep(60);

    return 0;
}