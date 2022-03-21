#ifndef FRACTALS_H
# define FRACTALS_H

# include <inttypes.h>
# include "../math/cnumber.h"
# include "../defines.h"

/* SETS */
typedef uint32_t	(*t_set_function)(t_cnumber pos, t_cnumber modif,
						uint32_t iteration_limit);

uint32_t		setfunc_mandelbrot(t_cnumber pos, t_cnumber modif,
					uint32_t iteration_limit);
uint32_t		setfunc_julia(t_cnumber pos, t_cnumber modif,
					uint32_t iteration_limit);
uint32_t		setfunc_burningship(t_cnumber pos, t_cnumber modif,
					uint32_t iteration_limit);
uint32_t		setfunc_tricorn(t_cnumber pos, t_cnumber modif,
					uint32_t iteration_limit);
uint32_t		setfunc_null(t_cnumber pos, t_cnumber modif,
					uint32_t iteration_limit);

/* GET BY ENUM */
enum e_fractal_set
{
	set_mandelbrot = 1,
	set_julia,
	set_burningship,
	set_tricorn,
};

t_set_function	get_fractal_set_function(enum e_fractal_set set);

#endif //!FRACTALS_H