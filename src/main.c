#include "session.h"
#include "lease.h"

int main(void)
{
    session_init();

lease_load("sample.leases");

session_dump();
    
    

    

    return 0;
}