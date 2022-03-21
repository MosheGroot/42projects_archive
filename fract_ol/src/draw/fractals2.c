#include "fractals.h"
#include <math.h>

/* TRICORN */
uint32_t	setfunc_tricorn(t_cnumber pos, t_cnumber modif,
				uint32_t iteration_limit)
{
	t_cnumber	z;
	long double	tmp_r;

	(void)modif;
	z = pos;
	for (uint32_t it = 1; it < iteration_limit; ++it)
	{
		tmp_r = z.r;
		z.r = z.r * z.r - z.i * z.i + pos.r;
		z.i = -2. * tmp_r * z.i + pos.i;
		if (z.r * z.r + z.i * z.i > 4.)
			return (it);
	}
	return (iteration_limit);
}
