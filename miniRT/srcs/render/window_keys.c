#include "window.h"

void    switch_zoom(int key, t_frame *frame)
{
    if (key == 69)
        frame->zoom *= 0.95;
    else
        frame->zoom *= 1.05;
    frame->rendered = 0;
}

void    switch_cam(int key, t_frame *frame)
{
    if (!frame->curr_cam)
        return ;
    if (key == 126)
        frame->curr_cam = frame->curr_cam->next;
    else if (key == 125)
        frame->curr_cam = frame->curr_cam->prev;
    frame->rendered = 0;
}

int     close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->mlx_win);
    lst_delete(&(data->frame.scene.cams), &free);
    lst_delete(&(data->frame.scene.lights), &free);
    lst_delete(&(data->frame.scene.objs), &free);
    exit(0);
    return (0);
}
