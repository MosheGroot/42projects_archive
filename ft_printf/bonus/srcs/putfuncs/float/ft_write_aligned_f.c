#include "ft_printf.h"

static int	count_n_write_f_buf(t_long_num *f_buf, int precision, int mode)
{
	int		out;

	out = 1;
	if (mode == WRITE)
	{
		write(1, ".", 1);
		write(1, f_buf->data, MIN((unsigned)precision, f_buf->len));
	}
	out += MIN((unsigned)precision, f_buf->len);
	precision = ((unsigned)precision > f_buf->len) ?
					((unsigned)precision - f_buf->len) : 0;
	out += precision;
	while (mode == WRITE && (precision-- > 0))
		write(1, "0", 1);
	return (out);
}

static int	write_aligned_f_left(double nbr, t_printdata *data,
									t_long_num *i_buf, t_long_num *f_buf)
{
	int		out;
	int		signs;

	signs = count_n_write_sign_f(data, nbr, 1);
	out = i_buf->len + signs;
	write(1, i_buf->data, i_buf->len);
	if (data->precision != 0 || (data->modifs & ALTERFORM))
		out += count_n_write_f_buf(f_buf, data->precision, WRITE);
	out += fill_width_num(data, out, ' ');
	free(f_buf->data);
	free(i_buf->data);
	return (out);
}

static int	write_aligned_f_right(double nbr, t_printdata *data,
									t_long_num *i_buf, t_long_num *f_buf)
{
	int		write_flag;
	int		signs;
	int		out;
	int		frac_len;

	write_flag = WRITE;
	if ((data->modifs & WIDTH) && (data->modifs & ZEROCOMPL))
		write_flag = NOTWR;
	signs = count_n_write_sign_f(data, nbr, !write_flag);
	if (data->precision != 0 || (data->modifs & ALTERFORM))
		frac_len = count_n_write_f_buf(f_buf, data->precision, NOTWR);
	else
		frac_len = 0;
	out = fill_width_num(data, i_buf->len + frac_len + signs, 0);
	out += count_n_write_sign_f(data, nbr, write_flag) + i_buf->len;
	write(1, i_buf->data, i_buf->len);
	if (data->precision != 0 || (data->modifs & ALTERFORM))
		out += count_n_write_f_buf(f_buf, data->precision, WRITE);
	free(f_buf->data);
	free(i_buf->data);
	return (out);
}

int			write_aligned_f(t_printdata *data, double nbr)
{
	t_long_num	i_buf;
	t_long_num	f_buf;
	int			out;

	if (is_inf(nbr) || is_nan(nbr) || data->precision == PREC_LIMIT)
		return (write_limit(data, nbr));
	else if (get_buffers_f(nbr, &i_buf, &f_buf, data->precision) == -1)
		return (-1);
	if (data->modifs & LEFTALIGN)
		out = write_aligned_f_left(nbr, data, &i_buf, &f_buf);
	else
		out = write_aligned_f_right(nbr, data, &i_buf, &f_buf);
	return (out);
}
