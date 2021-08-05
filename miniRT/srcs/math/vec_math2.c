#include "vec_math.h"

double  vec_dot(t_crd a, t_crd b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_crd   vec_cross_prod(t_crd a, t_crd b)
{
    t_crd   out;

    out.x = a.y * b.z - a.z * b.y;
    out.y = a.z * b.x - a.x * b.z;
    out.z = a.x * b.y - a.y * b.x;
    return (out);
}

t_crd   vec_sum(t_crd a, t_crd b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return (a);
}

t_crd   point_move_to(t_crd p, t_crd vec)
{
    p.x += vec.x;
    p.y += vec.y;
    p.z += vec.z;
    return (p);
}
