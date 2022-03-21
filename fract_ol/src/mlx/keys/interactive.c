#include "keys.h"
#include "../hooks.h"

int is_interactive_mode_keyboard_key(int key)
{
  return (key == KEY_CTRL);
}

void  change_interactive_mode(int key, t_data *data)
{
  if (key != KEY_CTRL)
    return ;
  if (!data->frame.interactive)
  {
    data->frame.interactive = 1;
    mlx_hook(data->mlx_win, 6, (1L << 6), mouse_move_hook_func, data);
  }
  else
  {
    data->frame.interactive = 0;
    mlx_hook(data->mlx_win, 6, (1L << 6), (void *)0, (void *)0);
  }
  data->frame.rendered = 0;
}
