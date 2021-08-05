#include "parser.h"
#include "render.h"

static void get_coeffs(t_crd *origin, t_crd *ray, t_obj *cyl, double *coeffs)
{
    t_crd   oc;

    oc = vec_get(*origin, cyl->coords[0]);
    coeffs[0] = pvec_dot(ray, ray)
        - pow(pvec_dot(ray, cyl->coords + 1), 2);
    coeffs[1] = 2 * (pvec_dot(ray, cyl->coords + 1)
            * pvec_dot(&oc, cyl->coords + 1) - pvec_dot(ray, &oc));
    coeffs[2] = pvec_dot(&oc, &oc)
        - pow(pvec_dot(&oc, cyl->coords + 1), 2)
        - (cyl->d * cyl->d / 4.);
}

double  cylinder_intersect(t_crd *origin, t_crd *ray, t_obj *cylinder)
{
    double  coeffs[3];
    double  d;
    double  t1;
    double  t2;

    get_coeffs(origin, ray, cylinder, coeffs);
    d = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];
    if (d < 0)
        return (INFINITY);
    t1 = (-1 * coeffs[1] - sqrt(d)) / (2 * coeffs[0]);
    t2 = (-1 * coeffs[1] + sqrt(d)) / (2 * coeffs[0]);
    if (t1 <= t2 && t1 > 0
        && fabs(vec_dot(vec_get(
                    cylinder->coords[0],
                    point_move_to(*origin, vec_mul(*ray, t1))),
                cylinder->coords[1])) < cylinder->len / 2.)
        return (t1);
    if (t2 > 0
        && fabs(vec_dot(vec_get(
                    cylinder->coords[0],
                    point_move_to(*origin, vec_mul(*ray, t2))),
                cylinder->coords[1])) < cylinder->len / 2.)
        return (t2);
    return (INFINITY);
}

t_crd    cylinder_normal_vec(const t_obj *cylinder, const t_crd *dest)
{
    t_crd   p;
    t_crd   c_moved;
    double  height;

    p = vec_get(cylinder->coords[0], *dest);
    height = vec_dot(cylinder->coords[1], p);
    c_moved = point_move_to(cylinder->coords[0],
            vec_mul(cylinder->coords[1], height));
    return (vec_normalize(vec_get(c_moved, *dest)));
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
    obj->coords[1] = vec_normalize(obj->coords[1]);
    *sh += delta;
    if (int_assigment(&delta, get_float(&(obj->d), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    if (int_assigment(&delta, get_float(&(obj->len), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    if (int_assigment(&delta, get_3t_uinteger(&(obj->col.r), &(obj->col.g),
                &(obj->col.b), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    return (0);
}

int    parse_cylinder(char *comm, t_scene *data)
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
    obj->get_inters_func = &cylinder_intersect;
    obj->get_normal_func = &cylinder_normal_vec;
    to_push = lst_new((void *)obj);
    if (!to_push)
        return (emergency_return_n_free((void *)obj, -2));
    lst_push_front(&(data->objs), to_push);
    return (sh);
}
