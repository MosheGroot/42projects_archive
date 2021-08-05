#include "window.h"
#include "norm_utilities.h"

void    put_pixel(t_image *img, t_xy_pair *pixel, unsigned int color)
{
    char    *dest;

    dest = img->addr + (img->line_size * pixel->y + img->bps * pixel->x / 8);
    *(unsigned int *)dest = color;
}

t_uint  t_col_to_ui(t_col *color)
{
    color->r = uint_ternary((color->r > 255), 255, color->r);
    color->g = uint_ternary((color->g > 255), 255, color->g);
    color->b = uint_ternary((color->b > 255), 255, color->b);
    return ((color->r << 16) + (color->g << 8) + color->b);
}

int hook_func(int key, t_data *data)
{
    if (key == 69 || key == 78)
        switch_zoom(key, &data->frame);
    else if (key == 126 || key == 125)
        switch_cam(key, &data->frame);
    else if (key == 53)
        close_window(data);
    if (!data->frame.rendered)
    {
        if (data->frame.curr_cam)
            render_frame(&data->frame);
        mlx_put_image_to_window(data->mlx, data->mlx_win,
            data->frame.img->img, 0, 0);
    }
    return (0);
}

static void prepare_mlx(t_data *data)
{
    data->frame.curr_cam = data->frame.scene.cams;
    data->frame.zoom = 1.;
    data->frame.rendered = 0;
    data->mlx = mlx_init();
    if (!data->mlx)
        log_errno("Can't init window! ");
    data->mlx_win = mlx_new_window(data->mlx,
            data->frame.res_x, data->frame.res_y, TITLE);
    if (!data->mlx_win)
        log_errno("Can't create window! ");
}

void    start_window(t_data *data)
{
    t_image     img;

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
    if (data->frame.curr_cam)
        render_frame(&data->frame);
    mlx_put_image_to_window(data->mlx, data->mlx_win,
        data->frame.img->img, 0, 0);
    mlx_hook(data->mlx_win, 2, 1L << 0, hook_func, data);
    mlx_hook(data->mlx_win, 17, 0, close_window, data);
    mlx_loop(data->mlx);
}
