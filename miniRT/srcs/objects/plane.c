#include "parser.h"
#include "render.h"

double  plane_intercept(t_crd *origin, t_crd *ray, t_obj *plane)
{
    t_crd   tmp_vec;
    double  a;
    double  b;

    tmp_vec = pvec_get(origin, plane->coords);
    a = pvec_dot(&tmp_vec, plane->coords + 1);
    b = pvec_dot(ray, plane->coords + 1);
    if (a / b >= 0)
        return (a / b);
    else
        return (1. / 0.);
}

t_crd   plane_normal_vec(t_obj *plane, t_crd *dest)
{
    (void)dest;
    return (plane->coords[1]);
}

static int  read_numbers(t_obj *obj, char *comm, int *sh)
{
    int    delta;

    *sh = 2;
    if (int_assigment(&delta, get_3float(&(obj->coords[0].x),
                &(obj->coords[0].y), &(obj->coords[0].z), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    if (int_assigment(&delta, get_3float(&(obj->coords[1].x),
                &(obj->coords[1].y), &(obj->coords[1].z), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    obj->coords[1] = vec_normalize(obj->coords[1]);
    *sh += delta;
    if (int_assigment(&delta, get_3t_uinteger(&(obj->col.r), &(obj->col.g),
                &(obj->col.b), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    return (0);
}

int     parse_plane(char *comm, t_scene *data)
{
    t_obj   *obj;
    t_list  *to_push;
    int     sh;
    int     status;

    obj = malloc(sizeof(t_obj));
    if (!obj)
        return (-2);
    if (int_assigment(&status, read_numbers(obj, comm, &sh)))
        return (status);
    while (ft_isspace(comm[sh]))
        sh++;
    if (comm[sh])
        return (emergency_return_n_free((void *)obj, -1));
    obj->get_inters_func = &plane_intercept;
    obj->get_normal_func = &plane_normal_vec;
    to_push = lst_new((void *)obj);
    if (!to_push)
        return (emergency_return_n_free((void *)obj, -2));
    lst_push_front(&(data->objs), to_push);
    return (sh);
}
