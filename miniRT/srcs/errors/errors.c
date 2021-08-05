#include "errors.h"

void    log_error(char *msg, int code)
{
    errno = code;
    perror(msg);
    exit(code);
}

void    log_errno(char *msg)
{
    perror(msg);
    exit(errno);
}
