#include "ft_printf.h"

static int	is_zero_to_space(t_printdata *data, long long nbr)
{
	int		res;

	res = 0;
	if ((data->modifs & PRECISION) && !data->precision && !nbr)
		res = 1;
	return (res);
}

static int	write_aligned_i_left(t_printdata *data, long long nbr)
{
	int		out;

	out = count_n_write_sign_i(data, nbr, WRITE);
	if (!is_zero_to_space(data, nbr))
		out += ft_putnbr_i(nbr, data->precision);
	out += fill_width_num(data, out, ' ');
	return (out);
}

static int	write_aligned_i_right(t_printdata *data, long long nbr, int num_len)
{
	int		write_flag;
	int		signs;
	int		out;

	if (is_zero_to_space(data, nbr))
		num_len = 0;
	if (data->modifs & PRECISION)
	{
		signs = count_n_write_sign_i(data, nbr, NOTWR);
		out = fill_width_num(data, MAX(num_len, data->precision) + signs, ' ');
		out += count_n_write_sign_i(data, nbr, WRITE);
		out += ft_putnbr_i(nbr, data->precision);
	}
	else
	{
		write_flag = WRITE;
		if ((data->modifs & WIDTH) && (data->modifs & ZEROCOMPL))
			write_flag = 0;
		signs = count_n_write_sign_i(data, nbr, !write_flag);
		out = fill_width_num(data, num_len + signs, 0);
		out += count_n_write_sign_i(data, nbr, write_flag);
		out += ft_putnbr_i(nbr, 1);
	}
	return (out);
}

int			write_aligned_i(t_printdata *data, long long nbr)
{
	int		out;
	int		num_len;

	if (data->precision < 0)
		set_default_precision(data, 1);
	num_len = count_digits_i(nbr);
	if (data->modifs & LEFTALIGN)
		out = write_aligned_i_left(data, nbr);
	else
		out = write_aligned_i_right(data, nbr, num_len);
	return (out);
}
