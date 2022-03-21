#include "keys.h"

int is_change_depth_keyboard_key(int key)
{
  return (key == KEY_Z || key == KEY_X);
}

void  change_depth(int key, t_frame *frame)
{
  if (key == KEY_Z)
  {
    if (frame->iterations_limit != FRACTOL_ITERATIONS_MIN)
    {
      frame->iterations_limit -= FRACTOL_ITERATIONS_CHANGE;
      frame->rendered = 0;
    }
  }
  else if (key == KEY_X)
  {
    if (frame->iterations_limit != FRACTOL_ITERATIONS_MAX)
    {
      frame->iterations_limit += FRACTOL_ITERATIONS_CHANGE;
      frame->rendered = 0;
    }
  }
}
