#include "hooks.h"
#include "keys/keys.h"
#include "window.h"

int mouse_move_hook_func(int x, int y, t_data *data)
{
  data->frame.mouse_pos.x = x;
  data->frame.mouse_pos.y = y;
  update_image(data);
  return (0);
}

int key_hook_func(int key, t_data *data)
{
  if (is_switch_set_keyboard_key(key))
    switch_set(key, &data->frame);
  else if (is_switch_colorset_keyboard_key(key))
    switch_colorset(key, &data->frame);
  else if (is_move_keyboard_key(key))
    move_origin_by_keyboard(key, &data->frame);
  else if (is_change_depth_keyboard_key(key))
    change_depth(key, &data->frame);
  else if (is_interactive_mode_keyboard_key(key))
    change_interactive_mode(key, data);
  else if (is_zoom_keyboard_key(key))
    switch_zoom_by_keyboard(key, &data->frame);
  else if (key == KEY_ESC)
    close_window(data);
  if (!data->frame.rendered)
    update_image(data);
  return (0);
}

int mouse_click_hook_func(int button, int x, int y, t_data *data)
{
  if (is_zoom_mouse_button(button))
    switch_zoom_by_mouse(button, x, y, &data->frame);
  else if (is_move_mouse_button(button))
    move_origin_by_mouse(x, y, &data->frame);
  else if (is_reset_mouse_button(button))
    reset_settings(&data->frame);
  if (!data->frame.rendered)
    update_image(data);
  return (0);
}
