#include "vec_math.h"

t_crd   vec_build(double x, double y, double z)
{
    t_crd   out;

    out.x = x;
    out.y = y;
    out.z = z;
    return (out);
}

t_crd   vec_get(t_crd a, t_crd b)
{
    b.x -= a.x;
    b.y -= a.y;
    b.z -= a.z;
    return (b);
}

double  vec_module(t_crd vec)
{
    return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_crd   vec_normalize(t_crd vec)
{
    double  module;

    module = vec_module(vec);
    vec.x /= module;
    vec.y /= module;
    vec.z /= module;
    return (vec);
}

t_crd   vec_mul(t_crd vec, double l)
{
    vec.x *= l;
    vec.y *= l;
    vec.z *= l;
    return (vec);
}
