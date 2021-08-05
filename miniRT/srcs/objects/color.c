#include "scene.h"
#include "norm_utilities.h"

t_col   color_get_default(void)
{
    t_col   out;

    out.r = 0;
    out.g = 0;
    out.b = 0;
    return (out);
}

t_col   color_mul(t_col col, double l)
{
    t_col   dest;

    dest.r = (unsigned int)(col.r * l);
    dest.g = (unsigned int)(col.g * l);
    dest.b = (unsigned int)(col.b * l);
    dest.r = uint_ternary((dest.r) > 255, 255, dest.r);
    dest.g = uint_ternary((dest.g) > 255, 255, dest.g);
    dest.b = uint_ternary((dest.b) > 255, 255, dest.b);
    return (dest);
}

t_col   color_add(t_col a, t_col b)
{
    t_col   dest;

    dest.r = a.r + b.r;
    dest.g = a.g + b.g;
    dest.b = a.b + b.b;
    dest.r = uint_ternary((dest.r) > 255, 255, dest.r);
    dest.g = uint_ternary((dest.g) > 255, 255, dest.g);
    dest.b = uint_ternary((dest.b) > 255, 255, dest.b);
    return (dest);
}
