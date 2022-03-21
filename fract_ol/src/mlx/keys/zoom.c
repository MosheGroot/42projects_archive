#include "keys.h"

static uint32_t   zoom_counter = 0;

static void       check_zoom_counter(t_frame *frame)
{
  if (zoom_counter == FRACTOL_ZOOM_SAME_ITERATION_LIMIT_STEP)
  {
    zoom_counter = 0;
    if (frame->iterations_limit != FRACTOL_ITERATIONS_MAX)
      frame->iterations_limit += FRACTOL_ITERATIONS_CHANGE;
  }
  else if (zoom_counter == 0)
  {
    zoom_counter = FRACTOL_ZOOM_SAME_ITERATION_LIMIT_STEP - 1;
    if (frame->iterations_limit != FRACTOL_ITERATIONS_MIN)
      frame->iterations_limit -= FRACTOL_ITERATIONS_CHANGE;
  }
}

int is_zoom_mouse_button(int key)
{
  return (key == MOUSE_WHEEL_UP
    || key == MOUSE_WHEEL_DOWN);
}

int is_zoom_keyboard_key(int key)
{
  return (key == KEY_PLUS
    || key == KEY_MINUS
    || key == KEY_NUM_PLUS
    || key == KEY_NUM_MINUS);
}

void  switch_zoom_by_mouse(int button, int x, int y, t_frame *frame)
{
  if (button == MOUSE_WHEEL_DOWN)
  {
    frame->zoom *= FRACTOL_ZOOM_DECREASE_ASPECT;
    zoom_counter -= 1;
  }
  else if (button == MOUSE_WHEEL_UP)
  {
    frame->zoom *= FRACTOL_ZOOM_INCREASE_ASPECT;
    zoom_counter += 1;
  }
  check_zoom_counter(frame);
  move_origin_by_mouse(x, y, frame);
}

void  switch_zoom_by_keyboard(int key, t_frame *frame)
{
  if (key == KEY_MINUS || key == KEY_NUM_MINUS)
  {
    frame->zoom *= FRACTOL_ZOOM_DECREASE_ASPECT;
    zoom_counter -= 1;
  }
  else if (key == KEY_PLUS || key == KEY_NUM_PLUS)
  { 
    frame->zoom *= FRACTOL_ZOOM_INCREASE_ASPECT;
    zoom_counter += 1;
  }
  check_zoom_counter(frame);
  frame->rendered = 0;
}
