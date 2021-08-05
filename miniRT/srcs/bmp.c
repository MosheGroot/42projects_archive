#include "window.h"
#include "bmp.h"

static t_bitmap_fileheader  prepare_fileheader(t_data *data)
{
    t_bitmap_fileheader out;

    out.bf_filesize = 2 + sizeof(t_bitmap_fileheader)
        + sizeof(t_bitmap_infoheader)
        + data->frame.res_x * data->frame.res_y * 4;
    out.bf_reserved1 = 0;
    out.bf_reserved2 = 0;
    out.bf_offs_bits = 0x36;
    return (out);
}

static t_bitmap_infoheader  prepare_infoheader(t_data *data)
{
    t_bitmap_infoheader out;

    out.bi_size = sizeof(out);
    out.bi_height = data->frame.res_y;
    out.bi_width = data->frame.res_x;
    out.bi_planes = 1;
    out.bi_bps = 32;
    out.bi_compression = 0;
    out.bi_image_size = 0;
    out.bi_x_pxs_per_meter = 6000;
    out.bi_y_pxs_per_meter = 6000;
    out.bi_colors_used = 0;
    out.bi_colors_important = 0;
    return (out);
}

void    prepare_bmp_file(int fd, t_data *data)
{
    t_bitmap_fileheader bmp_fh;
    t_bitmap_infoheader bmp_ih;
    unsigned short      bf_type;

    bf_type = 0x4d42;
    bmp_fh = prepare_fileheader(data);
    bmp_ih = prepare_infoheader(data);
    write(fd, &bf_type, sizeof(bf_type));
    write(fd, &bmp_fh, sizeof(bmp_fh));
    write(fd, &bmp_ih, sizeof(bmp_ih));
}
