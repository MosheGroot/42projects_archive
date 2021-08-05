#include "ft_printf.h"

int     ft_putchar_ext(t_printdata *data, char c)
{
    int out;

    out = 1;
    if (!(data->modifs & LEFTALIGN))
        out += fill_width_cs(data, 1);
    write(1, &c, 1);
    if (data->modifs & LEFTALIGN)
        out += fill_width_cs(data, 1);
    return (out);
}
