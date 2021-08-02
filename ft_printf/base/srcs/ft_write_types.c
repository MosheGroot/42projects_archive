#include "ft_printf.h"

int			write_ptr(t_printdata *data, va_list args)
{
	void	*ptr;

	if (data->precision < 0)
		set_default_precision(data, 1);
	ptr = va_arg(args, void *);
	data->modifs |= ALTERFORM;
	data->size = LL_SIZE;
	data->type = 'x';
	return (write_aligned_x(data, (unsigned long long)ptr, FORCE_ALTFORM));
}

int			write_percent(t_printdata *data)
{
	int		out;

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
