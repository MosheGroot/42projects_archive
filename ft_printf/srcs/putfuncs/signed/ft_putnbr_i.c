#include "ft_putnbr_i.h"

int         count_n_write_sign_i(t_printdata *data, long long nbr, int w)
{
    int     out;

    out = 0;
    if (nbr < 0)
    {
        if (w == WRITE)
            write(1, "-", 1);
        out = 1;
    }
    else if (data->modifs & SHOWSIGN)
    {
        if (w == WRITE)
            write(1, "+", 1);
        out = 1;
    }
    else if (data->modifs & SIGNSPACE)
    {
        if (w == WRITE)
            write(1, " ", 1);
        out = 1;
    }
    return (out);
}

int         count_digits_i(long long nbr)
{
    int     i;

    i = 1;
    while (nbr /= 10)
        i++;
    return (i);
}

int         ft_putnbr_i(long long nbr, int precision)
{
    int     out;
    char    c;

    if (nbr == 0 && precision <= 0)
        return (0);
    out = ft_putnbr_i(nbr / 10, precision - 1) + 1;
    c = ABS(nbr % 10) + '0';
    write(1, &c, 1);
    return (out);
}
