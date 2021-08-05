#include "window.h"

static t_crd    calc_pos(t_xy_pair *pixel, t_frame *frame, double fov_tan)
{
    double  x;
    double  y;
    double  aspect_ratio;
    t_crd   out;

    aspect_ratio = (double)frame->res_x / (double)frame->res_y;
    x = (2 * (pixel->x + 0.5) / frame->res_x - 1.) * aspect_ratio * fov_tan;
    y = (1 - 2 * (pixel->y + 0.5) / frame->res_y) * fov_tan;
    out.x = x * frame->zoom;
    out.y = y * frame->zoom;
    return (out);
}

t_crd   cast_ray(t_xy_pair *pixel, t_frame *frame, double fov_tan)
{
    t_crd   on_screen;
    t_crd   basis_nx;
    t_crd   basis_ny;
    t_cam   *cam;
    t_crd   ans;

    cam = ((t_cam *)frame->curr_cam->data);
    on_screen = calc_pos(pixel, frame, fov_tan);
    basis_nx = vec_mul(cam->basis_x, on_screen.x);
    basis_ny = vec_mul(cam->basis_y, on_screen.y);
    ans = vec_normalize(vec_sum(vec_sum(basis_nx, basis_ny), cam->dir));
    return (ans);
}

t_col   get_pxl_color(t_crd *origin, t_crd *ray, t_scene *scene)
{
    t_obj   *obj;
    t_col   out;
    t_light lght;
    t_crd   p;
    double  t;

    out = color_get_default();
    obj = check_intersection(origin, ray, scene->objs, &t);
    if (!obj)
        return (out);
    p = point_move_to(*origin, vec_mul(*ray, t - EPS));
    lght.pos = obj->get_normal_func(obj, &p);
    lght = get_light(&p, lght.pos, scene);
    out = color_add(color_mul(obj->col, lght.br), lght.col);
    return (out);
}
