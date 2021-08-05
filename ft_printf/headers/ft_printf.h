#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_printdata.h"
# include "ft_putnbr_i.h"
# include "ft_putnbr_ui.h"
# include "ft_putnbr_x.h"
# include "ft_put_to_ptr.h"
# include "ft_putnbr_f.h"

# define SUCCESS    1
# define ERROR      0

int        ft_printf(const char *format, ...);

int        write_integer(t_printdata *data, va_list args);
int        write_uinteger(t_printdata *data, va_list args);
int        write_xinteger(t_printdata *data, va_list args);
int        write_ptr(t_printdata *data, va_list args);
int        write_percent(t_printdata *data);

int        fill_width_cs(t_printdata *data, int value_len);
int        fill_width_num(t_printdata *data, int value_len, char space);

int        ft_putchar_ext(t_printdata *data, char c);
int        ft_putstr_ext(t_printdata *data, const char *str);

int        ft_putptr(void *ptr);

#endif
