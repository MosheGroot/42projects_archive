#ifndef FT_PUTNBR_X_H
# define FT_PUTNBR_X_H

# include "ft_printdata.h"

# define FORCE_ALTFORM  1
# define DEFFORM        0

int         ft_putnbr_x_ext(t_printdata *data, unsigned int nbr, int f);
int         ft_putnbr_hx_ext(t_printdata *data, unsigned short int nbr, int f);
int         ft_putnbr_lx_ext(t_printdata *data, unsigned long int nbr, int f);
int         ft_putnbr_hhx_ext(t_printdata *data, unsigned char nbr, int f);
int         ft_putnbr_llx_ext(t_printdata *data, unsigned long long nbr, int f);
int         write_aligned_x(t_printdata *data, unsigned long long nbr, int f);

int         count_n_write_sign_x(t_printdata *data, unsigned long long nbr,
                                int w, int f);
int         count_digits_x(unsigned long long nbr);
int         ft_putnbr_x(t_printdata *data, unsigned long long nbr);

#endif
