#ifndef WINDOW_H
# define WINDOW_H

# include <mlx.h>

# include "../draw/frame.h"

typedef struct s_data
{
  t_frame   frame;
  void    *mlx;
  void    *mlx_win;
} t_data;

void  start_window(t_data *data);
void  update_image(t_data *data);

#endif //!WINDOW_H