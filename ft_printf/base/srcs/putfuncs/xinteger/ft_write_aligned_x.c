#include "ft_printf.h"

static int	is_zero_to_space(t_printdata *data, unsigned long long nbr)
{
	int		res;

	res = 0;
	if ((data->modifs & PRECISION) && !data->precision && !nbr)
		res = 1;
	return (res);
}

static int	write_aligned_x_left(t_printdata *data, unsigned long long nbr,
									int f)
{
	int		out;

	out = count_n_write_sign_x(data, nbr, WRITE, f);
	if (!is_zero_to_space(data, nbr))
		out += ft_putnbr_x(data, nbr);
	out += fill_width_num(data, out, ' ');
	return (out);
}

static int	write_aligned_x_right(t_printdata *data, unsigned long long nbr,
									int num_len, int f)
{
	int		write_flag;
	int		signs;
	int		out;

	if (is_zero_to_space(data, nbr))
		num_len = 0;
	if (data->modifs & PRECISION)
	{
		signs = count_n_write_sign_x(data, nbr, NOTWR, f);
		out = fill_width_num(data, MAX(num_len, data->precision) + signs, ' ');
		out += count_n_write_sign_x(data, nbr, WRITE, f);
		out += ft_putnbr_x(data, nbr);
	}
	else
	{
		write_flag = WRITE;
		if ((data->modifs & WIDTH) && (data->modifs & ZEROCOMPL))
			write_flag = NOTWR;
		signs = count_n_write_sign_x(data, nbr, !write_flag, f);
		out = fill_width_num(data, num_len + signs, 0);
		out += count_n_write_sign_x(data, nbr, write_flag, f);
		out += ft_putnbr_x(data, nbr);
	}
	return (out);
}

int			write_aligned_x(t_printdata *data, unsigned long long nbr, int f)
{
	int		out;
	int		num_len;

	if (data->precision < 0)
		set_default_precision(data, 1);
	num_len = count_digits_x(nbr);
	if (data->modifs & LEFTALIGN)
		out = write_aligned_x_left(data, nbr, f);
	else
		out = write_aligned_x_right(data, nbr, num_len, f);
	return (out);
}
