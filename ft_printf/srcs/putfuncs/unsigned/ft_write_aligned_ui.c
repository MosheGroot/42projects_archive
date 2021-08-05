#include "ft_printf.h"

static int  is_zero_to_space(t_printdata *data, unsigned long long nbr)
{
    int     res;

    res = 0;
    if ((data->modifs & PRECISION) && !data->precision && !nbr)
        res = 1;
    return (res);
}

static int  write_aligned_ui_left(t_printdata *data, unsigned long long nbr)
{
    int     out;

    if (is_zero_to_space(data, nbr))
        out = 0;
    else
        out = ft_putnbr_ui(nbr, data->precision);
    out += fill_width_num(data, out, ' ');
    return (out);
}

static int  write_aligned_ui_right(t_printdata *data, unsigned long long nbr,
                                    int num_len)
{
    int     out;

    if (is_zero_to_space(data, nbr))
        num_len = 0;
    if (data->modifs & PRECISION)
        out = fill_width_num(data, MAX(num_len, data->precision), ' ');
    else
        out = fill_width_num(data, num_len, 0);
    if (!is_zero_to_space(data, nbr))
        out += ft_putnbr_ui(nbr, data->precision);
    return (out);
}

int     write_aligned_ui(t_printdata *data, unsigned long long nbr)
{
    int     out;
    int     num_len;

    num_len = count_digits_ui(nbr);
    if (data->modifs & LEFTALIGN)
        out = write_aligned_ui_left(data, nbr);
    else
        out = write_aligned_ui_right(data, nbr, num_len);
    return (out);
}
