# srcs files
SRCS_DIR= srcs
OBJS_DIR= objs
HDRS_DIR= headers

SRCS 	= $(addprefix $(SRCS_DIR)/, main.c	parser.c\
				$(addprefix init/, sems_init.c\
									philos_processes_init.c\
				)\
				$(addprefix processes/, additional_processes_init.c\
										philosopher_process.c\
										servicer_process.c\
										daemon_process.c\
										timestamps.c\
				)\
			)
HDRS 	= $(addprefix $(HDRS_DIR)/, philo_bonus.h)
OBJS 	= $(addprefix $(OBJS_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
VPATH	= $(addprefix $(SRCS_DIR), / /inits /processes)

# compile settings
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -lpthread #-fsanitize=address
NAME	= philo_bonus

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
