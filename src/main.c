#include "watcher.h"
#include "session.h"
#include <unistd.h>
#include "http.h"

int main(void)
{
    session_init();

    watcher_start("sample.leases");

    http_start();

    return 0;
}