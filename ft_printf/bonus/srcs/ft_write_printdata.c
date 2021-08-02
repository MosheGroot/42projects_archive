#include "ft_printf.h"

static int	width_overflow(int width)
{
	if (width == 2147483647 || width <= -2147483647)
		return (1);
	return (0);
}

int			write_data(t_printdata *data, va_list args, int cur_count)
{
	int		out;

	out = 0;
	if (width_overflow(data->width))
		out = -1;
	else if (data->type == 'c')
		out = ft_putchar_ext(data, va_arg(args, int));
	else if (data->type == 's')
		out = ft_putstr_ext(data, va_arg(args, char *));
	else if (data->type == 'd' || data->type == 'i')
		out = write_integer(data, args);
	else if (data->type == 'u')
		out = write_uinteger(data, args);
	else if (data->type == 'x' || data->type == 'X')
		out = write_xinteger(data, args);
	else if (data->type == 'p')
		out = write_ptr(data, args);
	else if (data->type == '%')
		out = write_percent(data);
	else if (data->type == 'n')
		out = write_to_ptr(data, args, cur_count);
	else if (data->type == 'f' || data->type == 'e' || data->type == 'g')
		out = write_float(data, va_arg(args, double));
	return (out);
}
