#include "ft_printf.h"

static int	width_overflow(int width)
{
	if (width == 2147483647 || width <= -2147483647)
		return (1);
	return (0);
}

int			write_data(t_printdata *data, va_list args)
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
		out = write_aligned_i(data, va_arg(args, int));
	else if (data->type == 'u')
		out = write_aligned_ui(data, va_arg(args, unsigned int));
	else if (data->type == 'x' || data->type == 'X')
		out = write_aligned_x(data,
				(unsigned long long)va_arg(args, unsigned int), DEFFORM);
	else if (data->type == 'p')
		out = write_ptr(data, args);
	else if (data->type == '%')
		out = write_percent(data);
	return (out);
}
