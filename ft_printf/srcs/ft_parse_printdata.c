#include "ft_printf.h"

static int      which_flag(char c)
{
    int     out;

    out = 0;
    if (c == '-')
        out = LEFTALIGN;
    else if (c == '+')
        out = SHOWSIGN;
    else if (c == '0')
        out = ZEROCOMPL;
    else if (c == '#')
        out = ALTERFORM;
    else if (c == ' ')
        out = SIGNSPACE;
    return (out);
}

static int      is_type(char c)
{
    int     out;

    out = 0;
    if (c == 'c' || c == 's')
        out = 1;
    else if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
        out = 2;
    else if (c == '%' || c == 'n' || c == 'p')
        out = 3;
    else if (c == 'g' || c == 'f' || c == 'e')
        out = 4;
    return (out);
}

static void     get_width_n_precision(t_printdata *data,
                    const char **format, va_list args)
{
    if (**format == '*')
    {
        data->width = va_arg(args, int);
        *format += 1;
    }
    else
        while (**format >= '0' && **format <= '9')
            data->width = data->width * 10 + (*((*format)++) - '0');
    if (data->width)
        data->modifs |= WIDTH;
    if (**format != '.')
        return ;
    *format += 1;
    data->precision = 0;
    if (**format == '*')
    {
        data->precision = va_arg(args, int);
        *format += 1;
    }
    else
        while (**format >= '0' && **format <= '9')
            data->precision = data->precision * 10 + (*((*format)++) - '0');
    data->modifs |= PRECISION;
}

static void     get_size(t_printdata *data, const char **format)
{
    if (**format == 'h')
    {
        *format += 1;
        if (**format == 'h')
        {
            data->size = HH_SIZE;
            *format += 1;
        }
        else
            data->size = H_SIZE;
    }
    else if (**format == 'l')
    {
        *format += 1;
        if (**format == 'l')
        {
            data->size = LL_SIZE;
            *format += 1;
        }
        else
            data->size = L_SIZE;
    }
}

t_printdata     parse_data(const char **format, va_list args)
{
    t_printdata     out;
    int             flag;
    const char      *copy;

    copy = *format;
    out = get_default_data();
    while ((flag = which_flag(*copy)))
    {
        out.modifs |= flag;
        copy++;
    }
    get_width_n_precision(&out, &copy, args);
    if (out.width < 0)
    {
        out.modifs |= LEFTALIGN;
        out.width *= -1;
    }
    get_size(&out, &copy);
    if (is_type(*copy))
    {
        out.type = *copy;
        *format = copy + 1;
    }
    return (out);
}
