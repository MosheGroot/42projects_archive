#include "ft_printf.h"

static int	ft_strlen(const char *str)
{
	int		len;

	len = 0;
	while (str[len++])
		;
	return (len - 1);
}

int			ft_putstr_ext(t_printdata *data, const char *str)
{
	int		len;
	int		out;

	if (!str)
		str = "(null)";
	out = 0;
	len = ft_strlen(str);
	if (data->modifs & PRECISION)
	{
		if (data->precision < 0)
			set_default_precision(data, len);
		else
			len = MIN(len, data->precision);
	}
	if (!(data->modifs & LEFTALIGN))
		out += fill_width_cs(data, len);
	write(1, str, len);
	out += len;
	if (data->modifs & LEFTALIGN)
		out += fill_width_cs(data, len);
	return (out);
}
