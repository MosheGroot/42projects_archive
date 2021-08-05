#include "vec_math.h"

t_crd   pvec_get(const t_crd *a, const t_crd *b)
{
    t_crd   out;

    out.x = b->x - a->x;
    out.y = b->y - a->y;
    out.z = b->z - a->z;
    return (out);
}

double  pvec_module(const t_crd *vec)
{
    return (sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

double  pvec_dot(const t_crd *a, const t_crd *b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_crd   pvec_cross_prod(const t_crd *a, const t_crd *b)
{
    t_crd   out;

    out.x = a->y * b->z - a->z * b->y;
    out.y = a->z * b->x - a->x * b->z;
    out.z = a->x * b->y - a->y * b->x;
    return (out);
}
