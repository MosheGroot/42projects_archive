#include "parser.h"
#include "render.h"

double  sphere_intersect(t_crd *origin, t_crd *ray, t_obj *sphere)
{
    t_crd   oc;
    double  oh;
    double  h2;
    double  hp;

    oc = pvec_get(origin, sphere->coords);
    oh = pvec_dot(&oc, ray);
    if (oh < 0)
        return (INFINITY);
    h2 = pvec_dot(&oc, &oc) - oh * oh;
    if (h2 > sphere->d * sphere->d / 4.)
        return (INFINITY);
    hp = sqrt(sphere->d * sphere->d / 4. - h2);
    if (oh - hp > 0 && oh + hp > 0)
        return (double_ternary((oh - hp < oh + hp), oh - hp, oh + hp));
    else if (oh - hp > 0)
        return (oh - hp);
    else if (oh + hp > 0)
        return (oh + hp);
    return (INFINITY);
}

t_crd   sphere_normal_vec(const t_obj *sphere, const t_crd *dest)
{
    t_crd   out;

    out = vec_normalize(pvec_get(sphere->coords, dest));
    return (out);
}

static int  read_numbers(t_obj *obj, char *comm, int *sh)
{
    int     delta;

    *sh = 2;
    if (int_assigment(&delta, get_3float(&(obj->coords[0].x),
                &(obj->coords[0].y), &(obj->coords[0].z), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    if (int_assigment(&delta, get_float(&(obj->d), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    if (int_assigment(&delta, get_3t_uinteger(&(obj->col.r), &(obj->col.g),
                &(obj->col.b), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    return (0);
}

int     parse_sphere(char *comm, t_scene *data)
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
    obj->get_inters_func = &sphere_intersect;
    obj->get_normal_func = &sphere_normal_vec;
    to_push = lst_new((void *)obj);
    if (!to_push)
        return (emergency_return_n_free((void *)obj, -2));
    lst_push_front(&(data->objs), to_push);
    return (sh);
}
