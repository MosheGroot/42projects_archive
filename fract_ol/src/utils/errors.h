#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>

void  log_error(char *msg, int code);

void  log_errno(char *msg);

#endif //!ERRORS_H