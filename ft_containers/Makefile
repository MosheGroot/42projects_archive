# Programm name
NAME = test
BNAME = bench

# Release compiler settings
CC = clang++
CFLAGS = -std=c++98 -Wall -Wextra -Werror -fsanitize=address -g

OBJS_DIR	= objs
HDRS_DIRS	= utils ft_vector ft_map test

# Headers dependences
HDRS := ft_vector.hpp ft_map.hpp ft_stack.hpp ft_set.hpp\
		$(addprefix data_structs/, ft_pair.hpp ft_rb_tree.hpp) \
		$(addprefix utils/, ft_meta.hpp ft_utils.hpp \
							ft_iterator.hpp ft_random_access_iterator.hpp\
							ft_reverse_iterator.hpp\
							) \
		tests/tests.hpp

# SRCS
TEST_SRCS := $(addprefix tests/, main.cpp \
						vector_tests.cpp \
						pair_tests.cpp \
						tree_tests.cpp \
						map_tests.cpp \
						stack_tests.cpp \
						set_tests.cpp \
					)

BENCH_SRCS := tests/benchmark.cpp

# OBJS
TEST_OBJS := $(addprefix $(OBJS_DIR)/, \
				$(notdir $(patsubst %.cpp, %.o, $(TEST_SRCS))))
BENCH_OBJS := $(addprefix $(OBJS_DIR)/, \
				$(notdir $(patsubst %.cpp, %.o, $(BENCH_SRCS))))

VPATH := . ./tests/

# compile rules
$(OBJS_DIR)/%.o: %.cpp $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

# unit tests rule
$(NAME): $(OBJS_DIR) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(NAME)

# benchmark rules
$(BNAME)_std: $(OBJS_DIR) $(BENCH_OBJS)
	$(CC) $(CFLAGS) $(BENCH_OBJS) -D STD -o $(BNAME)_std

$(BNAME)_ft: $(OBJS_DIR) $(BENCH_OBJS)
	$(CC) $(CFLAGS) $(BENCH_OBJS) -D FT -o $(BNAME)_ft

benchmark: $(OBJS_DIR) $(BENCH_OBJS) 	$(BNAME)_std $(BNAME)_ft
	@echo "==================="
	@echo -n "std: "; time ./$(BNAME)_std $$RANDOM
	@echo "==================="
	@echo -n "ft: "; time ./$(BNAME)_ft $$RANDOM
	@echo "==================="

# additional rules
clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	rm -f $(BNAME)_*
	rm -rf $(OBJS_DIR)

re:		fclean	$(NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

.PHONY:	benchmark fclean clean re all
