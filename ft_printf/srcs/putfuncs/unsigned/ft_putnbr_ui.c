#include "ft_putnbr_i.h"

int     count_digits_ui(unsigned long long nbr)
{
    int     i;

    i = 1;
    while (nbr /= 10)
        i++;
    return (i);
}

int     ft_putnbr_ui(unsigned long long nbr, int precision)
{
    int     out;
    char    c;

    if (nbr == 0 && precision <= 0)
        return (0);
    out = ft_putnbr_i(nbr / 10, precision - 1) + 1;
    c = nbr % 10 + '0';
    write(1, &c, 1);
    return (out);
}
