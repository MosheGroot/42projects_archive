#ifndef FRAME_H
# define FRAME_H

# include "../mlx/image.h"
# include "../defines.h"
# include "colors.h"
# include "fractals.h"

typedef struct s_xy_pair_ld
{
  long double x;
  long double y;
}     t_xy_pair_ld;

typedef struct s_xy_pair_ui
{
  uint32_t  x;
  uint32_t  y;
}     t_xy_pair_ui;


typedef struct s_frame
{
  uint32_t      res_x;
  uint32_t      res_y;
  t_image       *img;
  int         rendered;

  long double     zoom;
  t_xy_pair_ld    origin;
  uint32_t      iterations_limit;

  int         interactive;
  t_xy_pair_ui    mouse_pos;

  enum e_fractal_set  set;
  enum e_colorset   colorset;
}     t_frame;


typedef struct s_render_segment
{
  uint32_t      begin_y;
  uint32_t      end_y;
  t_cnumber     modif;
  t_frame       *frame;
}      t_render_segment;


void    render_frame(t_frame *frame);

#endif //!FRAME_H