#include "ft_printf.h"

int     fill_width_cs(t_printdata *data, int value_len)
{
    char    space;
    int     out;

    space = ' ';
    out = (data->width - value_len > 0) ? (data->width - value_len) : 0;
    while (data->width > value_len++)
        write(1, &space, 1);
    return (out);
}

int     fill_precision_num(t_printdata *data, int digit_count)
{
    int     out;
    char    space;

    out = data->precision - digit_count;
    out = (out > 0) ? out : 0;
    space = '0';
    while (data->precision > digit_count++)
        write(1, &space, 1);
    return (out);
}

int     fill_width_num(t_printdata *data, int value_len, char space)
{
    int     out;

    out = data->width - value_len;
    out = (out > 0) ? out : 0;
    if (!space)
    {
        if (data->modifs & ZEROCOMPL)
            space = '0';
        else
            space = ' ';
    }
    while (data->width > value_len++)
        write(1, &space, 1);
    return (out);
}
