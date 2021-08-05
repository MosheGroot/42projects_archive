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

# SRCS SECTION
SRCS_M_NAMES		= ft_printf.c

SRCS_TOPRNT_NAMES	= ft_printdata_struct.c\
                        ft_parse_printdata.c\
                        ft_write_printdata.c\
                        ft_write_types.c\
                        ft_write_types2.c\
                        ft_fill_width.c

SRCS_PUT_NAMES	= ft_putchar_ext.c\
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


SRCS_M			= $(addprefix ./srcs/,$(SRCS_M_NAMES))
SRCS_TOPRNT		= $(addprefix ./srcs/,$(SRCS_TOPRNT_NAMES))
SRCS_PUT		= $(addprefix ./srcs/putfuncs/,$(SRCS_PUT_NAMES))

OBJS			= 	$(SRCS_M:.c=.o)\
                    $(SRCS_TOPRNT:.c=.o)\
                    $(SRCS_PUT:.c=.o)

HEADERS_DIR		= ./headers/

# END OF SRCS


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
	$(CC) $(CFLAGS) $< -o $@ -c -I$(HEADERS_DIR)


# RULES
all:			$(NAME)

$(NAME):    $(OBJS)
			ar -crs $(NAME) $(OBJS)
			ranlib $(NAME)
                
clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:			fclean $(NAME)
		

# DEBUG SECTION
debug:		$(NAME) $(OBJS_D)
		    $(CC) -g $(OBJS_D) $(NAME) -o $(NAME_DBG) -I$(HEADERS_DIR)

clean_d:	clean
			rm -f $(OBJS_D)

fclean_d:	clean_d
			rm -f $(NAME_DBG)
			rm -f $(NAME)

.PHONY:		clean fclean re all debug clean_d fclean_d
