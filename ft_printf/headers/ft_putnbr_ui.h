#ifndef FT_PUTNBR_UI_H
# define FT_PUTNBR_UI_H

# include "ft_printdata.h"

int         ft_putnbr_ui_ext(t_printdata *data, unsigned int nbr);
int         ft_putnbr_uhi_ext(t_printdata *data, unsigned short int nbr);
int         ft_putnbr_uli_ext(t_printdata *data, unsigned long int nbr);
int         ft_putnbr_uhhi_ext(t_printdata *data, unsigned char nbr);
int         ft_putnbr_ulli_ext(t_printdata *data, unsigned long long nbr);
int         write_aligned_ui(t_printdata *data, unsigned long long nbr);

int         count_digits_ui(unsigned long long nbr);
int         ft_putnbr_ui(unsigned long long nbr, int precision);

#endif
