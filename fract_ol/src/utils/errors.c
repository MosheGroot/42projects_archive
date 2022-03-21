#include "errors.h"

#include <stdio.h>
#include <stdlib.h>

void	log_error(char *msg, int code)
{
	errno = code;
	perror(msg);
	exit(code);
}

void	log_errno(char *msg)
{
	perror(msg);
	exit(errno);
}
