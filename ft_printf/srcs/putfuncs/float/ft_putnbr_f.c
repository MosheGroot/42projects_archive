#include "ft_printf.h"

static int  free_dbl(t_long_num *int_buf, t_long_num *frac_buf)
{
    if (int_buf->data)
        free(int_buf->data);
    if (frac_buf->data)
        free(frac_buf->data);
    return (-1);
}

static void round_buffers(t_long_num *int_buf, t_long_num *frac_buf,
                            size_t precision)
{
    t_long_num  one;
    size_t      i;
    int         rounded;

    one.data = "1";
    one.len = 1;
    rounded = 0;
    i = frac_buf->len - precision;
    while (++i <= frac_buf->len)
        if (frac_buf->data[frac_buf->len - i] == '9')
            frac_buf->data[frac_buf->len - i] = '0';
        else
        {
            frac_buf->data[frac_buf->len - i] += 1;
            rounded = 1;
            break ;
        }
    if (!rounded)
        lar_add(int_buf, &one);
}

static void round_half(t_long_num *int_buf, t_long_num *frac_buf,
                            size_t precision)
{
    t_long_num  one;

    one.data = "1";
    one.len = 1;
    if (precision > 0 && ((frac_buf->data[precision - 1] - '0') % 2))
    {
        if (frac_buf->data[precision - 1] != '9')
            frac_buf->data[precision - 1] += 1;
        else
            round_buffers(int_buf, frac_buf, precision);
    }
    else
    {
        if ((int_buf->data[int_buf->len - 1] - '0') % 2)
            lar_add(int_buf, &one);
    }
}

void        round_lar_buffs(t_long_num *int_buf, t_long_num *frac_buf,
                            size_t precision)
{
    if (precision < frac_buf->len)
    {
        if (precision == frac_buf->len && frac_buf->data[precision] == '5')
            round_half(int_buf, frac_buf, precision);
        else if (precision == 0 && frac_buf->len == 1 &&
                                            frac_buf->data[precision] == '5')
            round_half(int_buf, frac_buf, precision);
        else if (frac_buf->data[precision] > '4')
            round_buffers(int_buf, frac_buf, precision);
    }
}

int         get_buffers_f(double nbr, t_long_num *int_buf, t_long_num *frac_buf,
                            size_t precision)
{
    int                 exp;
    unsigned long long  m;

    exp = EXP_MASK(DBL_MASK(nbr));
    exp -= 1023;
    m = VAL_MASK(DBL_MASK(nbr));
    if (!(*int_buf = ft_bufnbr_fint(m, exp)).data)
        return (-1);
    if (!(*frac_buf = ft_bufnbr_ffrac(m, exp)).data)
        return (free_dbl(int_buf, frac_buf));
    round_lar_buffs(int_buf, frac_buf, precision);
    return (0);
}
