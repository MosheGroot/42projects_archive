#include "window.h"
#include "norm_utilities.h"

static t_uint   min(t_uint a, t_uint b)
{
    if (a < b)
        return (a);
    return (b);
}

static void     *render_segment(void *data)
{
    t_render_segment    *segment;
    t_crd               cam_ray;
    t_crd               origin;
    t_col               pxl_col;
    t_xy_pair           pixel;

    segment = (t_render_segment *)data;
    origin = ((t_cam *)segment->frame->curr_cam->data)->pos;
    pixel.y = segment->begin_y;
    while (pixel.y < segment->end_y)
    {
        pixel.x = 0;
        while (pixel.x < segment->frame->res_x)
        {
            cam_ray = cast_ray(&pixel, segment->frame, segment->fov_tan);
            pxl_col = get_pxl_color(&origin, &cam_ray, &segment->frame->scene);
            put_pixel(segment->frame->img, &pixel, t_col_to_ui(&pxl_col));
            pixel.x++;
        }
        pixel.y++;
    }
    pthread_exit(0);
}

void    render_frame(t_frame *frame)
{
    t_render_segment    segms[TH];
    pthread_t           thread_ids[TH];
    pthread_attr_t      attr;
    t_uint              stp;
    int                 i;

    stp = frame->res_y / uint_ternary((TH <= frame->res_y), TH, frame->res_y);
    segms[0].fov_tan = tan(((t_cam *)frame->curr_cam->data)->fov * M_PI / 360.);
    segms[0].frame = frame;
    segms[0].end_y = 0;
    i = -1;
    while (++i < TH)
    {
        segms[i] = segms[(i - 1) * (i != 0)];
        segms[i].begin_y = segms[i].end_y;
        segms[i].end_y = min(segms[i].begin_y + stp + 1, frame->res_y);
        if (segms[i].end_y > frame->res_y)
            segms[i].end_y = frame->res_y;
        pthread_attr_init(&attr);
        pthread_create(thread_ids + i, &attr, &render_segment, segms + i);
    }
    i = 0;
    while (i++ < TH)
        pthread_join(thread_ids[i - 1], NULL);
    frame->rendered = 1;
}
