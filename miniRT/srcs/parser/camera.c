#include "parser.h"

static void fill_cam_basis(const t_crd *dir, t_crd *b_x, t_crd *b_y)
{
    if (fabs(vec_dot(*dir, vec_build(1, 0, 0))) < 0.5)
        *b_x = vec_build(1, 0, 0);
    else
        *b_x = vec_build(0, 0, 1);
    *b_y = vec_normalize(pvec_cross_prod(dir, b_x));
    *b_x = vec_normalize(pvec_cross_prod(dir, b_y));
    if (b_y->y < 0)
        *b_y = vec_mul(*b_y, -1.);
    if (dir->z < 0 && b_x->x > 0)
        *b_x = vec_mul(*b_x, -1.);
    else if (dir->z > 0 && b_x->x < 0)
        *b_x = vec_mul(*b_x, -1.);
}

static int  read_numbers(t_cam *cam, char *comm, ssize_t *sh)
{
    ssize_t delta;

    delta = get_3float(&(cam->pos.x), &(cam->pos.y), &(cam->pos.z), comm + *sh);
    if (delta == -1)
        return (emergency_return_n_free((void *)cam, -1));
    *sh += delta;
    delta = get_3float(&(cam->dir.x), &(cam->dir.y), &(cam->dir.z), comm + *sh);
    if (delta == -1)
        return (emergency_return_n_free((void *)cam, -1));
    *sh += delta;
    cam->dir = vec_normalize(cam->dir);
    delta = get_t_uinteger(&(cam->fov), comm + *sh);
    if (delta == -1)
        return (emergency_return_n_free((void *)cam, -1));
    *sh += delta;
    return (0);
}

int     parse_camera(char *comm, t_scene *data)
{
    t_cam   *cam;
    t_list  *to_push;
    ssize_t sh;
    int     status;

    sh = 1;
    cam = malloc(sizeof(t_cam));
    if (!cam)
        return (-2);
    status = read_numbers(cam, comm, &sh);
    if (cam->fov > 179)
        cam->fov = 179;
    if (status)
        return (status);
    while (ft_isspace(comm[sh]))
        sh++;
    if (comm[sh])
        return (emergency_return_n_free((void *)cam, -1));
    fill_cam_basis(&cam->dir, &cam->basis_x, &cam->basis_y);
    to_push = lst_new((void *)cam);
    if (!to_push)
        return (emergency_return_n_free((void *)cam, -2));
    lst_push_back(&(data->cams), to_push);
    return (sh);
}
