#include "ft_printf.h"

int     write_to_ptr(t_printdata *data, va_list args, int cur_count)
{
    if (data->size == DEF_SIZE)
        (ft_putcount_to_ptr(va_arg(args, int *), cur_count));
    else if (data->size == H_SIZE)
        (ft_putcount_to_hptr(va_arg(args, short int *), cur_count));
    else if (data->size == L_SIZE)
        (ft_putcount_to_lptr(va_arg(args, long int *), cur_count));
    else if (data->size == HH_SIZE)
        (ft_putcount_to_hhptr(va_arg(args, signed char *), cur_count));
    else if (data->size == LL_SIZE)
        (ft_putcount_to_llptr(va_arg(args, long long *), cur_count));
    return (0);
}

int     write_float(t_printdata *data, double f_num)
{
    int out;

    out = 0;
    if (!(data->modifs & PRECISION) ||
            (data->precision < 0 && data->precision != PREC_LIMIT))
        set_default_precision(data, 6);
    if (data->type == 'f')
        out = write_aligned_f(data, f_num);
    else if (data->type == 'e')
        out = write_aligned_e(data, f_num);
    return (out);
}
