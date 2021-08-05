#ifndef ERRORS_H
# define ERRORS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

int		log_message(char *msg, int code);
void	log_error(char *msg, int code);
void	log_errno(char *msg);

#endif
