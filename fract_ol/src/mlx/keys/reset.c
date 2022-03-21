#include "keys.h"

int is_reset_mouse_button(int key)
{
  return (key == MOUSE_KEY_RIGHT);
}

void  reset_settings(t_frame *frame)
{
  frame->interactive = 0;
  frame->iterations_limit = FRACTOL_ITERATION_DEFAULT_LIMIT;
  frame->origin.x = 0.;
  frame->origin.y = 0.;
  frame->zoom = FRACTOL_ZOOM_DEFAULT;
  frame->rendered = 0;
}
