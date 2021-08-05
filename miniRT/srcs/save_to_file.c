#include "window.h"
#include "bmp.h"
#include <unistd.h>
#include <fcntl.h>

static void     write_image(int fd, t_frame *frame)
{
    char    *src;
    ssize_t i;

    i = frame->res_y - 1;
    while (i >= 0)
    {
        src = frame->img->addr + i * frame->img->line_size;
        write(fd, src, frame->img->line_size);
        i--;
    }
}

static void     set_default_params(t_data *data)
{
    t_image *img;

    img = malloc(sizeof(t_image));
    if (!img)
        log_errno("Error\nCan't allocate memory to save picture 1 ");
    img->addr = malloc(sizeof(t_uint) * data->frame.res_x * data->frame.res_y);
    if (!img->addr)
        log_errno("Error\nCan't allocate memory to save picture 2 ");
    img->bps = 32;
    img->line_size = data->frame.res_x * (img->bps / 8);
    data->frame.img = img;
    data->frame.curr_cam = data->frame.scene.cams;
    data->frame.zoom = 1.;
    data->frame.rendered = 0;
}

void    save_to_file(t_data *data, const char *filename)
{
    int     fd;

    set_default_params(data);
    render_frame(&data->frame);
    fd = open(filename, O_CREAT | O_WRONLY, 0666);
    if (fd < 0)
        log_errno("Error\nCan't open file to writing ");
    prepare_bmp_file(fd, data);
    write_image(fd, &data->frame);
    close(fd);
    lst_delete(&(data->frame.scene.cams), &free);
    lst_delete(&(data->frame.scene.lights), &free);
    lst_delete(&(data->frame.scene.objs), &free);
    free(data->frame.img->addr);
    free(data->frame.img);
}
