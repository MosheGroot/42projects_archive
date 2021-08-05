#include "ft_printf.h"

int     write_integer(t_printdata *data, va_list args)
{
    long long   nbr;

    if (data->precision < 0)
        set_default_precision(data, 1);
    nbr = -1;
    if (data->size == DEF_SIZE)
        nbr = (int)va_arg(args, int);
    else if (data->size == H_SIZE)
        nbr = (short int)va_arg(args, int);
    else if (data->size == L_SIZE)
        nbr = (long int)va_arg(args, long int);
    else if (data->size == HH_SIZE)
        nbr = (signed char)va_arg(args, int);
    else if (data->size == LL_SIZE)
        nbr = va_arg(args, long long);
    return (write_aligned_i(data, nbr));
}

int     write_uinteger(t_printdata *data, va_list args)
{
    unsigned long long  nbr;

    if (data->precision < 0)
        set_default_precision(data, 1);
    nbr = -1;
    if (data->size == DEF_SIZE)
        nbr = (unsigned int)va_arg(args, unsigned int);
    else if (data->size == H_SIZE)
        nbr = (unsigned short int)va_arg(args, unsigned int);
    else if (data->size == L_SIZE)
        nbr = (unsigned long int)va_arg(args, unsigned long int);
    else if (data->size == HH_SIZE)
        nbr = (unsigned char)va_arg(args, unsigned int);
    else if (data->size == LL_SIZE)
        nbr = va_arg(args, unsigned long long);
    return (write_aligned_ui(data, nbr));
}

int     write_xinteger(t_printdata *data, va_list args)
{
    unsigned long long  nbr;

    if (data->precision < 0)
        set_default_precision(data, 1);
    nbr = -1;
    if (data->size == DEF_SIZE)
        nbr = (unsigned int)va_arg(args, unsigned int);
    else if (data->size == H_SIZE)
        nbr = (unsigned short int)va_arg(args, unsigned int);
    else if (data->size == L_SIZE)
        nbr = (unsigned long int)va_arg(args, unsigned long int);
    else if (data->size == HH_SIZE)
        nbr = (unsigned char)va_arg(args, unsigned int);
    else if (data->size == LL_SIZE)
        nbr = va_arg(args, unsigned long long);
    return (write_aligned_x(data, nbr, DEFFORM));
}

int     write_ptr(t_printdata *data, va_list args)
{
    void    *ptr;

    if (data->precision < 0)
        set_default_precision(data, 1);
    ptr = va_arg(args, void *);
    data->modifs |= ALTERFORM;
    data->size = LL_SIZE;
    data->type = 'x';
    return (write_aligned_x(data, (unsigned long long)ptr, FORCE_ALTFORM));
}

int     write_percent(t_printdata *data)
{
    int     out;

    out = 1;
    if (data->modifs & LEFTALIGN)
    {
        write(1, "%", 1);
        out += fill_width_num(data, 1, ' ');
    }
    else
    {
        out += fill_width_num(data, 1, 0);
        write(1, "%", 1);
    }
    return (out);
}
