#include "ft_printf.h"

int     is_nan(double num)
{
    return (num != num);
}

int     is_inf(double num)
{
    signed char             out;
    unsigned long long      mask;
    unsigned long long      m;
    unsigned long long      e;
    unsigned char           sign;

    mask = DBL_MASK(num);
    m = VAL_MASK(mask);
    e = EXP_MASK(mask);
    sign = mask & SIGN_BIT;
    out = 0;
    if (!m && e == 2047)
    {
        if (sign)
            out = -1;
        else
            out = 1;
    }
    return (out);
}

int     count_n_write_sign_f(t_printdata *data, double nbr, int w)
{
    if (DBL_MASK(nbr) & SIGN_BIT)
    {
        if (w == WRITE)
            write(1, "-", 1);
        return (1);
    }
    else if ((data->modifs & SHOWSIGN) && !is_nan(nbr))
    {
        if (w == WRITE)
            write(1, "+", 1);
        return (1);
    }
    else if ((data->modifs & SIGNSPACE) && !is_nan(nbr))
    {
        if (w == WRITE)
            write(1, " ", 1);
        return (1);
    }
    return (0);
}

int     write_limit(t_printdata *data, double nbr)
{
    int     out;

    out = 3 + count_n_write_sign_f(data, nbr, NOTWR);
    if (!(data->modifs & LEFTALIGN))
        out += fill_width_num(data, out, ' ');
    count_n_write_sign_f(data, nbr, WRITE);
    if (is_inf(nbr) || (data->precision == PREC_LIMIT && data->type == 'f'))
        write(1, "inf", 3);
    else if (is_nan(nbr))
        write(1, "nan", 3);
    if (data->modifs & LEFTALIGN)
        out += fill_width_num(data, out, ' ');
    if (data->precision == PREC_LIMIT)
        out = -1;
    return (out);
}
