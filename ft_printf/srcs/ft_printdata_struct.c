#include "ft_printf.h"

t_printdata     get_default_data(void)
{
    t_printdata out;

    out.modifs = 0;
    out.width = 0;
    out.precision = 1;
    out.size = DEF_SIZE;
    out.type = 0;
    return (out);
}

void            set_default_precision(t_printdata *data, int prec)
{
    data->precision = prec;
    if (data->modifs & PRECISION)
        data->modifs &= ~PRECISION;
}
