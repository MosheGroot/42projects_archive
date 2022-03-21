#include "keys.h"

#include <stdlib.h>

int close_window(t_data *data)
{
  mlx_destroy_window(data->mlx, data->mlx_win);
  exit(0);
  return (0);
}
