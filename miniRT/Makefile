# DIREDCTORIES
HEADERS     = ./headers/
OBJS_DIR    = ./objs
SRCS_DIR    = ./srcs/
MLX_DIR     = ./minilibx-linux

SRCS_DIR_LIST   = $(addprefix $(SRCS_DIR), get_next_line/\
                                        list/ math/ objects/\
                                        render/ parser/ errors/) $(SRCS_DIR)

# HEADERS
HDRS        =   $(addprefix $(HEADERS), bmp.h errors.h get_next_line.h list.h norm_utilities.h\
                                        parser.h render.h scene.h vec_math.h window.h)

# SRCS FILES
SCRS_MAIN   =   main.c norm_utilities.c bmp.c save_to_file.c\
                errors/errors.c
SRCS_GNL    =   $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)
SRCS_LST    =   $(addprefix list/,          list.c list2.c)
SRCS_MATH   =   $(addprefix math/,          vec_math.c vec_math2.c vec_math_ptrs.c)
SRCS_OBJS   =   $(addprefix objects/,       color.c cylinder.c plane.c sphere.c square.c triangle.c)
SRCS_RND    =   $(addprefix render/,        render.c render2.c render3.c window.c window_keys.c)	
SRCS_PRS    =   $(addprefix parser/,        ato_funcs.c camera.c parser_utils.c parser.c parser2.c)	
SRCS        =   $(addprefix $(SRCS_DIR), $(SCRS_MAIN) $(SRCS_GNL) $(SRCS_LST) \
                            $(SRCS_MATH) $(SRCS_OBJS) $(SRCS_RND) $(SRCS_PRS))

OBJS    = $(addprefix objs/, $(notdir $(patsubst %.c, %.o, $(SRCS))))

VPATH   = $(SRCS_DIR_LIST)

# COMPILE SETTINGS
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror 
NAME	= miniRT
MLX_NAME= $(MLX_DIR)/libmlx.a

$(OBJS_DIR)/%.o : %.c $(HDRS) Makefile
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(HEADERS) -c $< -o $@

all:	$(NAME)

$(NAME):    $(MLX_NAME) $(OBJS_DIR) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MLX_DIR) -lmlx -lpthread -lm -lGL -lX11 -lXext

$(MLX_NAME):
	make -C $(MLX_DIR)
        
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)

re:     fclean all
