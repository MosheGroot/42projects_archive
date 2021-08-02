# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgroot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 12:28:29 by mgroot            #+#    #+#              #
#    Updated: 2020/11/15 15:32:31 by mgroot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BASE SECTION
BASE_SRCS_M_NAMES		= ft_printf.c

BASE_SRCS_TOPRNT_NAMES	= ft_printdata_struct.c\
						  ft_parse_printdata.c\
						  ft_write_printdata.c\
						  ft_write_types.c\
						  ft_fill_width.c

BASE_SRCS_PUT_NAMES		= ft_putchar_ext.c\
						  ft_putstr_ext.c\
						  signed/ft_write_aligned_i.c\
						  signed/ft_putnbr_i.c\
						  unsigned/ft_write_aligned_ui.c\
						  unsigned/ft_putnbr_ui.c\
						  xinteger/ft_write_aligned_x.c\
						  xinteger/ft_putnbr_x.c


BASE_SRCS_M			= $(addprefix ./base/srcs/,$(BASE_SRCS_M_NAMES))
BASE_SRCS_TOPRNT	= $(addprefix ./base/srcs/,$(BASE_SRCS_TOPRNT_NAMES))
BASE_SRCS_PUT		= $(addprefix ./base/srcs/putfuncs/,$(BASE_SRCS_PUT_NAMES))

BASE_OBJS			= 	$(BASE_SRCS_M:.c=.o)\
						$(BASE_SRCS_TOPRNT:.c=.o)\
						$(BASE_SRCS_PUT:.c=.o) 

BASE_HEAD			= 		./base/headers/
# END OF BASE SECTION


# BONUS SECTION
BONUS_SRCS_M_NAMES		= ft_printf.c

BONUS_SRCS_TOPRNT_NAMES	= ft_printdata_struct.c\
						  ft_parse_printdata.c\
						  ft_write_printdata.c\
						  ft_write_types.c\
						  ft_write_types2.c\
						  ft_fill_width.c

BONUS_SRCS_PUT_NAMES	= ft_putchar_ext.c\
						  ft_putstr_ext.c\
						  ft_put_to_ptr.c\
						  signed/ft_write_aligned_i.c\
						  signed/ft_putnbr_i.c\
						  unsigned/ft_write_aligned_ui.c\
						  unsigned/ft_putnbr_ui.c\
						  xinteger/ft_write_aligned_x.c\
						  xinteger/ft_putnbr_x.c\
						  float/ft_write_aligned_f.c\
						  float/ft_write_aligned_e.c\
						  float/ft_putnbr_f.c\
						  float/ft_putnbr_f2.c\
						  float/ft_float_ext_funcs.c\
						  float/ft_e_ext_funcs.c\
						  float/long_arifmetic/lar_add.c\
						  float/long_arifmetic/lar_mul1.c\
						  float/long_arifmetic/lar_mul2.c\
						  float/long_arifmetic/lar_base.c\
						  float/long_arifmetic/lar_fracadd.c\
						  float/long_arifmetic/lar_fracmul.c


BONUS_SRCS_M			= $(addprefix ./bonus/srcs/,$(BONUS_SRCS_M_NAMES))
BONUS_SRCS_TOPRNT		= $(addprefix ./bonus/srcs/,$(BONUS_SRCS_TOPRNT_NAMES))
BONUS_SRCS_PUT			= $(addprefix ./bonus/srcs/putfuncs/,$(BONUS_SRCS_PUT_NAMES))

BONUS_OBJS				= 	$(BONUS_SRCS_M:.c=.o)\
							$(BONUS_SRCS_TOPRNT:.c=.o)\
						   	$(BONUS_SRCS_PUT:.c=.o) 

BONUS_HEAD				= ./bonus/headers/
# END OF BONUS SECTION


# DEBUG
SRCS_DBG	= ./debug/dbg.c

OBJS_D		= $(SRCS_DBG:.c=.o)
# END OF DEBUG


# COMPILE SETTINGS
CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

NAME_DBG	= a.out

NAME		= libftprintf.a

%.o: %.c
		$(if $(findstring base/,$@),\
			$(CC) $(CFLAGS) $< -o $@ -c -I$(BASE_HEAD),\
			$(CC) $(CFLAGS) $< -o $@ -c -I$(BONUS_HEAD)\
		)


# RULES
all:			$(NAME)

$(NAME):		$(BASE_OBJS)
				ar -crs $(NAME) $(BASE_OBJS)
				ranlib $(NAME)

bonus:			$(BONUS_OBJS)
				ar -crs $(NAME) $(BONUS_OBJS)
				ranlib $(NAME)
				
clean:
			rm -f $(BASE_OBJS)
			rm -f $(BONUS_OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)
			

# DEBUG SECTION
debug_b:		$(OBJS_D) bonus
			$(CC) -g $(OBJS_D) $(NAME) -o $(NAME_DBG) -I$(BONUS_HEAD)

debug:		$(OBJS_D) all
			$(CC) -g $(OBJS_D) $(NAME) -o $(NAME_DBG) -I$(BASE_HEAD)

clean_d:	clean
			rm -f $(OBJS_D)

fclean_d:	clean_d
			rm -f $(NAME_DBG)
			rm -f $(NAME)

# NORMINETTE RULES
norm:
			norminette ./base/headers/
			norminette $(BASE_SRCS_M)
			norminette $(BASE_SRCS_TOPRNT)
			norminette $(BASE_SRCS_PUT)

norm_b:
			norminette ./bonus/headers/
			norminette $(BONUS_SRCS_M)
			norminette $(BONUS_SRCS_TOPRNT)
			norminette $(BONUS_SRCS_PUT)

.PHONY:		clean fclean re all norm norm_b bonus debug clean_d fclean_d
