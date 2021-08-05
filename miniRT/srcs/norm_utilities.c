#include "norm_utilities.h"

t_uint  uint_ternary(int result, t_uint true_v, t_uint false_v)
{
    if (result)
        return (true_v);
    return (false_v);
}

int     int_ternary(int result, int true_v, int false_v)
{
    if (result)
        return (true_v);
    return (false_v);
}

double  double_ternary(int result, double true_v, double false_v)
{
    if (result)
        return (true_v);
    return (false_v);
}

int     int_assigment(int *dest, int value)
{
    *dest = value;
    return (value);
}

void    *void_ptr_assigment(void **dest, void *value)
{
    *dest = value;
    return (value);
}
