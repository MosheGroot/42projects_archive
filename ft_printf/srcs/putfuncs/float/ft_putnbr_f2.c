#include "ft_printf.h"

static t_long_num   *get_pow2(t_long_num *pow2, int cur_n, int new_n)
{
    t_long_num  two;

    two.data = "2";
    two.len = 1;
    if (new_n > 0)
    {
        while (++cur_n <= new_n)
            if (!lar_mul(pow2, &two))
                return (NULL);
    }
    else if (new_n < 0)
        while (--cur_n >= new_n)
        {
            if (!lar_fracmul_2(pow2))
                return (NULL);
        }
    return (pow2);
}

static t_long_num   *get_pow2_buffer(t_long_num *pow2, int *count,
                                        int *exp, int mode)
{
    if (mode == INT_MODE)
    {
        *pow2 = lar_getnum(1);
        *count = 0;
        if (*exp > 52)
        {
            if (!get_pow2(pow2, 0, *exp - 52))
                return (NULL);
            *count = *exp - 52;
            *exp = 52;
        }
    }
    else if (mode == FRAC_MODE)
    {
        *pow2 = lar_getnum(5);
        *count = -1;
        if (*exp < 0)
        {
            if (!get_pow2(pow2, -1, *exp))
                return (NULL);
            *count = *exp;
        }
    }
    return (pow2);
}

static t_long_num   free_bufs(t_long_num *pow2, t_long_num *zero_buf)
{
    if (pow2->data)
        free(pow2->data);
    if (zero_buf->data)
        free(zero_buf->data);
    zero_buf->data = NULL;
    return (*zero_buf);
}

t_long_num          ft_bufnbr_fint(unsigned long long m, int exp)
{
    int         count;
    int         i;
    t_long_num  pow2;
    t_long_num  out;

    if (exp < 0)
        return (lar_getnum(0));
    if (!(out = lar_getnum(0)).data)
        return (out);
    if (!get_pow2_buffer(&pow2, &count, &exp, INT_MODE)->data)
        return (free_bufs(&pow2, &out));
    i = 52 - exp;
    while (i < 52)
    {
        if (m & (1llu << (i++)))
            if (!lar_add(&out, &pow2))
                return (free_bufs(&pow2, &out));
        if (!get_pow2(&pow2, count, count + 1))
            return (free_bufs(&pow2, &out));
        count++;
    }
    lar_add(&out, &pow2);
    free(pow2.data);
    return (out);
}

t_long_num          ft_bufnbr_ffrac(unsigned long long m, int exp)
{
    int         count;
    int         i;
    t_long_num  pow2;
    t_long_num  out;

    if (exp >= 52)
        return (lar_getnum(0));
    if (!(out = lar_getnum(0)).data)
        return (out);
    if (!get_pow2_buffer(&pow2, &count, &exp, FRAC_MODE))
        return (free_bufs(&pow2, &out));
    (exp < 0 && exp != -1023) ? lar_add(&out, &pow2) : 0;
    i = (exp >= 0) ? (52 - exp) : 53 - (exp == -1023);
    while (i > 0 && m)
    {
        if (m & (1llu << (--i)))
            if (!lar_fracadd(&out, &pow2))
                return (free_bufs(&pow2, &out));
        if (!get_pow2(&pow2, count, count - 1))
            return (free_bufs(&pow2, &out));
        count--;
    }
    free(pow2.data);
    return (out);
}
