#ifndef FT_PUTNBR_X_H
# define FT_PUTNBR_X_H

# include "ft_printdata.h"

# define FORCE_ALTFORM	1
# define DEFFORM		0

int		write_aligned_x(t_printdata *data, unsigned long long nbr, int f);

int		count_n_write_sign_x(t_printdata *data, unsigned long long nbr,
								int w, int f);
int		count_digits_x(unsigned long long nbr);
int		ft_putnbr_x(t_printdata *data, unsigned long long nbr);

#endif
