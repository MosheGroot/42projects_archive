#ifndef FT_PRINTDATA_H
# define FT_PRINTDATA_H

# include <unistd.h>
# include <stdarg.h>
# include "mini_math.h"

# define LEFTALIGN	(1 << 1)
# define SHOWSIGN	(1 << 2)
# define ZEROCOMPL	(1 << 3)
# define ALTERFORM	(1 << 4)
# define SIGNSPACE	(1 << 5)
# define PRECISION	(1 << 6)
# define WIDTH		(1 << 7)

# define LL_SIZE	1
# define L_SIZE		2
# define H_SIZE		3
# define HH_SIZE	4
# define DEF_SIZE	0

typedef struct		s_printdata
{
	char			modifs;
	int				width;
	int				precision;
	int				size;
	char			type;
}					t_printdata;

t_printdata			get_default_data(void);
void				set_default_precision(t_printdata *data, int prec);

t_printdata			parse_data(const char **format, va_list args);

int					write_data(t_printdata *data, va_list args);

#endif
