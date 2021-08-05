#include "long_arifmetic.h"
#include <stdio.h>

static size_t   count_zeros_2(const t_long_num *a, size_t *ovfl)
{
    size_t  count;

    *ovfl = 0;
    count = 0;
    while (a->data[count] == '0' && a->data[count])
        count++;
    if ((a->data[count] - '0') / 2 == 0)
        *ovfl = 1;
    return (count);
}

static size_t   count_digits_lambda(const t_long_num *a, unsigned char l,
                                    size_t zeros)
{
    size_t  count;
    int     rem;

    rem = 0;
    count = 0;
    while (++count + zeros <= a->len)
        rem = ((a->data[a->len - count] - '0') * l + rem) / 10;
    if (rem)
        count++;
    return (count - 1);
}

static void     mul(t_long_num *dest, const t_long_num *a, unsigned char l,
                    size_t zeros)
{
    size_t  i;
    int     rem;
    int     tmp;

    i = 0;
    rem = 0;
    while (++i + zeros <= a->len)
    {
        tmp = (a->data[a->len - i] - '0') * l + rem;
        dest->data[dest->len - i] = tmp % 10 + '0';
        rem = tmp / 10;
    }
    if (rem)
        dest->data[dest->len - i] = rem + '0';
}

t_long_num      *lar_fracmul_2(t_long_num *a)
{
    t_long_num  buf;
    size_t      num_len;
    size_t      zeros;
    size_t      i;
    size_t      ovfl;

    zeros = count_zeros_2(a, &ovfl);
    num_len = count_digits_lambda(a, 5, zeros);
    buf.len = zeros + ovfl + num_len;
    buf.data = (char *)malloc(sizeof(char) * (buf.len + 1));
    if (!buf.data)
        return (NULL);
    buf.data[buf.len] = '\0';
    i = 0;
    while (i < zeros + ovfl)
        buf.data[i++] = '0';
    mul(&buf, a, 5, zeros);
    free(a->data);
    *a = buf;
    return (a);
}
