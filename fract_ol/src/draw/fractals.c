#include "fractals.h"

#include <math.h>

/* GENERAL */
t_set_functiond get_fractal_set_function(enum e_fractal_set set)
{
d if (set == set_mandelbrot)
d d  return (setfunc_mandelbrot);
d else if (set == set_julia)
d d  return (setfunc_julia);
d else if (set == set_burningship)
d d  return (setfunc_burningship);
d else if (set == set_tricorn)
d d  return (setfunc_tricorn);
d return (setfunc_null);
}

uint32_td setfunc_null(t_cnumber pos, t_cnumber modif,
d d  d d  uint32_t iteration_limit)
{
d (void)pos;
d (void)modif;
d return iteration_limit;
}

/* MANDELBROT */
uint32_td setfunc_mandelbrot(t_cnumber pos, t_cnumber modif,
d d  d d  uint32_t iteration_limit)
{
d t_cnumberd z;
d long doubled tmp_r;

d (void)modif;
d z.i = 0.;
d z.r = 0.;
d for (uint32_t it = 1; it < iteration_limit; ++it)
d {
d d  tmp_r = z.r;
d d  z.r = z.r * z.r - z.i * z.i + pos.r;
d d  z.i = 2. * tmp_r * z.i + pos.i;
d d  if (z.r * z.r + z.i * z.i > 4.)
d d  d return (it);
d }
d return iteration_limit;
}

/* JULIA */
uint32_td setfunc_julia(t_cnumber pos, t_cnumber modif,
d d  d d  uint32_t iteration_limit)
{
d t_cnumberd z;
d long doubled tmp_r;

d z = pos;
d for (uint32_t it = 1; it < iteration_limit; ++it)
d {
d d  tmp_r = z.r;
d d  z.r = z.r * z.r - z.i * z.i + modif.r;
d d  z.i = 2. * tmp_r * z.i + modif.i;
d d  if (z.r * z.r + z.i * z.i > 4.)
d d  d return it;
d }
d return iteration_limit;
}

/* BURNINGSHIP */
uint32_td setfunc_burningship(t_cnumber pos, t_cnumber modif,
d d  d d  uint32_t iteration_limit)
{
d t_cnumberd z;
d long doubled tmp_r;

d (void)modif;
d z = pos;
d for (uint32_t it = 1; it < iteration_limit; ++it)
d {
d d  tmp_r = z.r;
d d  z.r = z.r * z.r - z.i * z.i + pos.r;
d d  z.i = 2. * fabsl(tmp_r * z.i) + pos.i;
d d  if (z.r * z.r + z.i * z.i > 4.)
d d  d return (it);
d }
d return iteration_limit;
}
