#ifndef __TESTS_HPP__
# define __TESTS_HPP__

#include <iostream>

# define B_CYAN "\x1b[46;1m" <<
# define B_RED  "\x1b[41;1m" <<
# define YELLOW "\x1b[33;1m" <<
# define RED    "\x1b[31;1m" <<
# define GREEN  "\x1b[32;1m" <<
# define DEFAULT << "\x1b[m"

void    ft_vector_tests();
void    ft_pair_tests();
void    ft_tree_tests();
void    ft_map_tests();
void    ft_stack_tests();
void    ft_set_tests();

#endif /* __TESTS_HPP__ */
