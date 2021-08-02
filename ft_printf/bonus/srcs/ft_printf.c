#include "ft_printf.h"

static int	parse_flag(const char **format, va_list args, int count)
{
	t_printdata	cur;
	int			out;

	*format += 1;
	out = 0;
	cur = parse_data(format, args);
	if (cur.type)
		out = write_data(&cur, args, count);
	return (out);
}

int			ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;
	int			prev;

	va_start(args, format);
	count = 0;
	prev = 0;
	while (*format)
	{
		if (*format == '%')
		{
			count += parse_flag(&format, args, count);
			if (prev > count)
				return (-1);
			prev = count;
		}
		else
		{
			write(1, format++, 1);
			count++;
		}
	}
	return (count);
}
