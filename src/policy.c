#include "policy.h"
#include "platform.h"
#include "stddef.h"

void policy_apply(subscriber_session_t *session)
{
    if (session == NULL)
        return;

    switch (session->status) {

    case STATUS_BLOCKED:
        platform_block(session->ip);
        break;

    case STATUS_ACTIVE:
        platform_allow(session->ip);
        break;

    default:
        break;
    }
}