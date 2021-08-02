#ifndef FT_PUTNBR_I_H
# define FT_PUTNBR_I_H

# include "ft_printdata.h"

# define WRITE	1
# define NOTWR	0

int		write_aligned_i(t_printdata *data, long long nbr);

int		count_n_write_sign_i(t_printdata *data, long long nbr, int w);
int		count_digits_i(long long nbr);
int		ft_putnbr_i(long long nbr, int precision);

#endif
