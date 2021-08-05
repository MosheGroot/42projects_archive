#include "ft_putnbr_i.h"

int         count_n_write_sign_x(t_printdata *data, unsigned long long nbr,
                                int w, int f)
{
    if ((data->modifs & ALTERFORM) && (nbr || f))
    {
        if (w)
        {
            write(1, "0", 1);
            write(1, &data->type, 1);
        }
        return (2);
    }
    return (0);
}

int         count_digits_x(unsigned long long nbr)
{
    int        i;

    i = 1;
    while (nbr /= 16)
        i++;
    return (i);
}

static int  ft_putnbr_rec(unsigned long long nbr, const char *base,
                            int precision)
{
    int     out;
    char    c;

    if (nbr == 0 && precision <= 0)
        return (0);
    out = ft_putnbr_rec(nbr / 16, base, precision - 1) + 1;
    c = base[nbr % 16];
    write(1, &c, 1);
    return (out);
}

int         ft_putnbr_x(t_printdata *data, unsigned long long nbr)
{
    int     out;

    if (data->type == 'x')
        out = ft_putnbr_rec(nbr, "0123456789abcdef", data->precision);
    else
        out = ft_putnbr_rec(nbr, "0123456789ABCDEF", data->precision);
    return (out);
}
