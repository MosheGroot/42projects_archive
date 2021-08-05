#include "parser.h"
#include "render.h"

static t_crd    get_first_basis(t_crd *normal)
{
    t_crd   basis_vec;

    basis_vec = vec_build(1, 0, 0);
    if (fabs(pvec_dot(normal, &basis_vec)
            / (pvec_module(normal) * pvec_module(&basis_vec))) > 1 - EPS)
        basis_vec = vec_build(0, 1, 0);
    return (basis_vec);
}

double  square_intercept(t_crd *origin, t_crd *ray, t_obj *plane)
{
    t_crd   tmp_vec;
    t_crd   basis_vec1;
    t_crd   basis_vec2;
    double  t;

    tmp_vec = pvec_get(origin, plane->coords);
    t = pvec_dot(&tmp_vec, plane->coords + 1);
    t /= pvec_dot(ray, plane->coords + 1);
    if (t < 0)
        return (INFINITY);
    basis_vec1 = get_first_basis(plane->coords + 1);
    basis_vec2 = pvec_cross_prod(plane->coords + 1, &basis_vec1);
    tmp_vec = vec_get(plane->coords[0],
            point_move_to(*origin, vec_mul(*ray, t)));
    if (fabs(pvec_dot(&tmp_vec, &basis_vec1)) > plane->d / 2.)
        return (INFINITY);
    if (fabs(pvec_dot(&tmp_vec, &basis_vec2)) > plane->d / 2.)
        return (INFINITY);
    return (t);
}

t_crd   square_normal_vec(t_obj *plane, t_crd *dest)
{
    (void)dest;
    return (plane->coords[1]);
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
    if (int_assigment(&delta, get_3t_uinteger(&(obj->col.r), &(obj->col.g),
                &(obj->col.b), comm + *sh)) == -1)
        return (emergency_return_n_free((void *)obj, -1));
    *sh += delta;
    return (0);
}

int     parse_square(char *comm, t_scene *data)
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
    obj->get_inters_func = &square_intercept;
    obj->get_normal_func = &square_normal_vec;
    to_push = lst_new((void *)obj);
    if (!to_push)
        return (emergency_return_n_free((void *)obj, -2));
    lst_push_front(&(data->objs), to_push);
    return (sh);
}
