#ifndef LONG_ARIFMETIC_H
# define LONG_ARIFMETIC_H

# include <stdlib.h>
# include <stddef.h>
# include "mini_math.h"

typedef struct        s_long_num
{
    char    *data;
    size_t  len;
}                    t_long_num;

t_long_num              lar_getnum(unsigned long long num);
t_long_num              lar_mul_lambda(const t_long_num *a, unsigned char l);

t_long_num              *lar_sizeinc(t_long_num *buf, size_t delta);

t_long_num              *lar_add(t_long_num *a, const t_long_num *b);
t_long_num              *lar_mul_10(t_long_num *a, size_t n);
t_long_num              *lar_mul(t_long_num *a, const t_long_num *b);

t_long_num              *lar_fracadd(t_long_num *a, const t_long_num *b);
t_long_num              *lar_fracmul_2(t_long_num *a);

#endif
