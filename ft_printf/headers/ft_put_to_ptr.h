#ifndef FT_PUT_TO_PTR_H
# define FT_PUT_TO_PTR_H

void    ft_putcount_to_ptr(int *ptr, int cur_count);
void    ft_putcount_to_hptr(short int *ptr, int cur_count);
void    ft_putcount_to_hhptr(signed char *ptr, int cur_count);
void    ft_putcount_to_lptr(long int *ptr, int cur_count);
void    ft_putcount_to_llptr(long long *ptr, int cur_count);

int     write_to_ptr(t_printdata *data, va_list args, int cur_count);

#endif
