#include "window.h"
#include "hooks.h"
#include "keys/keys.h"

#include "../utils/errors.h"

void  display_tips(t_data *data)
{
  if (data->frame.res_y < 300 && data->frame.res_y < 200)
    return ;
  mlx_string_put(data->mlx, data->mlx_win, 10, 10, COLOR_WHITE,
    "Move - WASD/arrows");
  mlx_string_put(data->mlx, data->mlx_win, 10, 40, COLOR_WHITE,
    "Move in place - mouse left buton");
  mlx_string_put(data->mlx, data->mlx_win, 10, 70, COLOR_WHITE,
    "Zoom in/out - scroll up/down and +/-");
  mlx_string_put(data->mlx, data->mlx_win, 10, 140, COLOR_WHITE,
    "Set prev/next - Q/E");
  mlx_string_put(data->mlx, data->mlx_win, 10, 170, COLOR_WHITE,
    "Depth down/up - Z/X");
  mlx_string_put(data->mlx, data->mlx_win, 10, 200, COLOR_WHITE,
    "Color palletes - 1/2/3");
  mlx_string_put(data->mlx, data->mlx_win, 10, 230, COLOR_WHITE,
    "Reset position/zoom/depth - mouse right buton");
  mlx_string_put(data->mlx, data->mlx_win, 10, 260, COLOR_WHITE,
    "Interactive mode on/off - CTRL");
  if (data->frame.interactive)
  {
    mlx_string_put(data->mlx, data->mlx_win, 10, 290, COLOR_RED,
      "Interactive mode ON");
  }
}

static void prepare_mlx(t_data *data)
{
  data->frame.res_x = 1500;
  data->frame.res_y = 1000;
  data->frame.zoom = FRACTOL_ZOOM_DEFAULT;
  data->frame.origin.x = 0.;
  data->frame.origin.y = 0.;
  data->frame.rendered = 0;
  data->frame.interactive = 0;
  data->frame.mouse_pos.x = 0;
  data->frame.mouse_pos.y = 0;
  data->frame.colorset = colorset_galactic;
  data->frame.iterations_limit = FRACTOL_ITERATION_DEFAULT_LIMIT;
    
  data->mlx = mlx_init();
  if (!data->mlx)
    log_errno("Can't init window! ");
    
  data->mlx_win = mlx_new_window(data->mlx,
      data->frame.res_x, data->frame.res_y, FRACTOL_WINDOW_TITLE);
  if (!data->mlx_win)
    log_errno("Can't create window! ");
}

void  update_image(t_data *data)
{
  render_frame(&data->frame);
  mlx_put_image_to_window(data->mlx, data->mlx_win,
    data->frame.img->img, 0, 0);
  display_tips(data);
}

void  start_window(t_data *data)
{
  t_image   img;

  prepare_mlx(data);
  
  data->frame.img = &img;
  img.img = mlx_new_image(data->mlx,
      data->frame.res_x, data->frame.res_y);
  if (!img.img)
    log_errno("Can't create image! ");
  img.addr = mlx_get_data_addr(img.img, &img.bps,
      &img.line_size, &img.endian);
  if (!img.addr)
    log_errno("Can't get image address! ");
    
  update_image(data);
    
  mlx_hook(data->mlx_win, 2, (1L << 0), key_hook_func, data);
  mlx_hook(data->mlx_win, 4, (1L << 0), mouse_click_hook_func, data);
  mlx_hook(data->mlx_win, 17, 0, close_window, data);
  mlx_loop(data->mlx);
}
