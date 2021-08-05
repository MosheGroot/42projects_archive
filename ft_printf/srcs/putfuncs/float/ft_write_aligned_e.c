#include "ft_printf.h"

static int  g_e;

static int  count_n_write_e(int mode)
{
    int     out;

    out = (count_digits_i(g_e) >= 2) ? (count_digits_i(g_e)) : 2;
    if (mode == WRITE)
    {
        write(1, (g_e >= 0) ? "e+" : "e-", 2);
        ft_putnbr_i(g_e, 2);
    }
    return (out + 2);
}

static int  count_n_write_fbuf(t_long_num *f_buf, int precision, int mode)
{
    int     out;

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
    out += count_n_write_e(mode);
    return (out);
}

static int  write_aligned_e_left(double nbr, t_printdata *data,
                                    t_long_num *i_buf, t_long_num *f_buf)
{
    int     out;
    int     signs;

    signs = count_n_write_sign_f(data, nbr, 1);
    out = signs + 1;
    write(1, i_buf->data, 1);
    if (data->precision != 0 || (data->modifs & ALTERFORM))
        out += count_n_write_fbuf(f_buf, data->precision, WRITE);
    else
        out += count_n_write_e(WRITE);
    out += fill_width_num(data, out, ' ');
    free(i_buf->data);
    free(f_buf->data);
    return (out);
}

static int  write_aligned_e_right(double nbr, t_printdata *data,
                                    t_long_num *i_buf, t_long_num *f_buf)
{
    int     write_flag;
    int     signs;
    int     out;
    int     f_len;

    write_flag = WRITE;
    if ((data->modifs & WIDTH) && (data->modifs & ZEROCOMPL))
        write_flag = NOTWR;
    signs = count_n_write_sign_f(data, nbr, !write_flag);
    if (data->precision != 0 || (data->modifs & ALTERFORM))
        f_len = count_n_write_fbuf(f_buf, data->precision, NOTWR);
    else
        f_len = count_n_write_e(NOTWR);
    out = fill_width_num(data, 1 + f_len + signs, 0);
    out += count_n_write_sign_f(data, nbr, write_flag) + 1;
    write(1, i_buf->data, 1);
    if (data->precision != 0 || (data->modifs & ALTERFORM))
        out += count_n_write_fbuf(f_buf, data->precision, WRITE);
    else
        out += count_n_write_e(WRITE);
    free(i_buf->data);
    free(f_buf->data);
    return (out);
}

int         write_aligned_e(t_printdata *data, double nbr)
{
    t_long_num  i_buf;
    t_long_num  f_buf;
    size_t      prev_len;

    if (is_inf(nbr) || is_nan(nbr) || data->precision == PREC_LIMIT)
        return (write_limit(data, nbr));
    else if (nbr == 0.)
    {
        i_buf = lar_getnum(0);
        f_buf = lar_getnum(0);
        g_e = 0;
    }
    else
    {
        if (get_buffers_f(nbr, &i_buf, &f_buf, -1) == -1)
            return (-1);
        g_e = move_to_sci_form(&i_buf, &f_buf);
        prev_len = i_buf.len;
        round_lar_buffs(&i_buf, &f_buf, data->precision);
        (prev_len != i_buf.len) ? (g_e++) : 0;
    }
    if (data->modifs & LEFTALIGN)
        return (write_aligned_e_left(nbr, data, &i_buf, &f_buf));
    else
        return (write_aligned_e_right(nbr, data, &i_buf, &f_buf));
}
