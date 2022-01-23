# srcs files
SRCS_DIR= srcs
OBJS_DIR= objs
HDRS_DIR= headers

SRCS 	= $(addprefix $(SRCS_DIR)/, main.c	parser.c\
				$(addprefix init/, forks_init.c\
									philos_data_init.c\
									philos_threads_init.c\
				)\
				$(addprefix threads/, additional_threads_init.c\
										philosopher_thread.c\
										servicer_thread.c\
										daemon_thread.c\
										timestamps.c\
				)\
			)
HDRS 	= $(addprefix $(HDRS_DIR)/, philo_one.h)
OBJS 	= $(addprefix $(OBJS_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
VPATH	= $(addprefix $(SRCS_DIR), / /inits /threads)

# compile settings
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -lpthread #-fsanitize=address #
NAME	= philo

$(OBJS_DIR)/%.o : %.c $(HDRS)
	$(CC) $(CFLAGS) -I$(HDRS_DIR) -c $< -o $@

# main rules
.PHONY:	all $(NAME) clean fclean re


all:	$(NAME)


$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean	$(NAME)
