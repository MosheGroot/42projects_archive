#include "parser.h"
#include "render.h"

static int  between_of_two(t_crd *a, t_crd *b, t_crd *c, t_crd *p)
{
    t_crd   vec1;
    t_crd   vec2;
    t_crd   vec3;
    double  tmp;

    vec1 = vec_normalize(pvec_get(a, b));
    vec2 = vec_normalize(pvec_get(a, c));
    vec3 = vec_normalize(pvec_get(a, p));
    tmp = vec_dot(vec1, vec2);
    if (tmp < vec_dot(vec1, vec3) && tmp < vec_dot(vec2, vec3))
        return (1);
    return (0);
}

double  triangle_intercept(t_crd *origin, t_crd *ray, t_obj *tr)
{
    t_crd   vec1;
    t_crd   vec2;
    t_crd   p;
    double  t;
    t_uint  i;

    vec1 = pvec_get(origin, tr->coords);
    vec2 = tr->get_normal_func(tr, &vec1);
    t = pvec_dot(&vec1, &vec2);
    t /= pvec_dot(ray, &vec2);
    if (t < 0)
        return (INFINITY);
    p = point_move_to(*origin, vec_mul(*ray, t));
    i = 0;
    while (i < 2)
    {
        if (!between_of_two(tr->coords + i, tr->coords + (i + 1) % 3,
                tr->coords + (i + 2) % 3, &p))
            return (INFINITY);
        i++;
    }
    return (t);
}

t_crd   triangle_normal_vec(t_obj *tr, t_crd *dest)
{
    (void)dest;
    return (vec_normalize(vec_cross_prod(
                vec_get(tr->coords[0], tr->coords[1]),
                vec_get(tr->coords[0], tr->coords[2]))));
}

static int  read_numbers(t_obj *obj, char *comm, int *sh)
{
    int     delta;

    *sh = 2;
    if (int_assigment(&delta, get_3float(&(obj->coords[0].x),
                &(obj->coords[0].y), &(obj->coords[0].z), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    if (int_assigment(&delta, get_3float(&(obj->coords[1].x),
                &(obj->coords[1].y), &(obj->coords[1].z), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    if (int_assigment(&delta, get_3float(&(obj->coords[2].x),
                &(obj->coords[2].y), &(obj->coords[2].z), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    if (int_assigment(&delta, get_3t_uinteger(&(obj->col.r), &(obj->col.g),
                &(obj->col.b), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    return (0);
}

int     parse_triangle(char *comm, t_scene *data)
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
    obj->get_inters_func = &triangle_intercept;
    obj->get_normal_func = &triangle_normal_vec;
    to_push = lst_new((void *)obj);
    if (!to_push)
        return (emergency_return_n_free((void *)obj, -2));
    lst_push_front(&(data->objs), to_push);
    return (sh);
}
