#ifndef FT_PUTNBR_F_H
# define FT_PUTNBR_F_H

# include "ft_printdata.h"
# include "long_arifmetic.h"

# define WRITE			1
# define NOTWR			0

# define FRAC_MODE		1
# define INT_MODE		2

# define DBL_MASK(d)	(*((unsigned long long *)&d))
# define EXP_MASK(d)	((d >> 52) & ((1llu << 11) - 1))
# define VAL_MASK(d)	(d & ((1llu << 52) - 1))
# define SIGN_BIT		(1llu << 63)

# define PREC_LIMIT		-2147483647

int			write_float(t_printdata *data, double nbr);
int			write_limit(t_printdata *data, double nbr);
int			write_aligned_f(t_printdata *data, double nbr);
int			write_aligned_e(t_printdata *data, double nbr);

int			count_n_write_sign_f(t_printdata *data, double nbr, int w);
int			get_buffers_f(double nbr, t_long_num *i_buf, t_long_num *f_buf,
							size_t precision);
void		round_lar_buffs(t_long_num *i_buf, t_long_num *f_buf, size_t prec);
int			move_to_sci_form(t_long_num *i_buf, t_long_num *f_buf);

t_long_num	ft_bufnbr_fint(unsigned long long m, int exp);
t_long_num	ft_bufnbr_ffrac(unsigned long long m, int exp);

int			is_inf(double num);
int			is_nan(double num);

#endif
