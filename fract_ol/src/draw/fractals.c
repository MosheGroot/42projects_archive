#include "fractals.h"

#include <math.h>

/* GENERAL */
t_set_function	get_fractal_set_function(enum e_fractal_set set)
{
	if (set == set_mandelbrot)
		return (setfunc_mandelbrot);
	else if (set == set_julia)
		return (setfunc_julia);
	else if (set == set_burningship)
		return (setfunc_burningship);
	else if (set == set_tricorn)
		return (setfunc_tricorn);
	return (setfunc_null);
}

uint32_t	setfunc_null(t_cnumber pos, t_cnumber modif,
				uint32_t iteration_limit)
{
	(void)pos;
	(void)modif;
	return iteration_limit;
}

/* MANDELBROT */
uint32_t	setfunc_mandelbrot(t_cnumber pos, t_cnumber modif,
				uint32_t iteration_limit)
{
	t_cnumber	z;
	long double	tmp_r;

	(void)modif;
	z.i = 0.;
	z.r = 0.;
	for (uint32_t it = 1; it < iteration_limit; ++it)
	{
		tmp_r = z.r;
		z.r = z.r * z.r - z.i * z.i + pos.r;
		z.i = 2. * tmp_r * z.i + pos.i;
		if (z.r * z.r + z.i * z.i > 4.)
			return (it);
	}
	return iteration_limit;
}

/* JULIA */
uint32_t	setfunc_julia(t_cnumber pos, t_cnumber modif,
				uint32_t iteration_limit)
{
	t_cnumber	z;
	long double	tmp_r;

	z = pos;
	for (uint32_t it = 1; it < iteration_limit; ++it)
	{
		tmp_r = z.r;
		z.r = z.r * z.r - z.i * z.i + modif.r;
		z.i = 2. * tmp_r * z.i + modif.i;
		if (z.r * z.r + z.i * z.i > 4.)
			return it;
	}
	return iteration_limit;
}

/* BURNINGSHIP */
uint32_t	setfunc_burningship(t_cnumber pos, t_cnumber modif,
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
		z.i = 2. * fabsl(tmp_r * z.i) + pos.i;
		if (z.r * z.r + z.i * z.i > 4.)
			return (it);
	}
	return iteration_limit;
}
