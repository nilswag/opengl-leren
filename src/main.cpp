#include "util/log.h"

int main()
{
    LOG_INFO("Hello %s!\n", "info");
    LOG_WARN("Hello %s!\n", "warn");
    LOG_ERROR("Hello %s!\n", "error");
    return 0;
}