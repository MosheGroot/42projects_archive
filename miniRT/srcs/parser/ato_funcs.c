#include <stddef.h>
#include "norm_utilities.h"

int     ft_isspace(char c)
{
    int     out;

    out = 0;
    if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        out = 1;
    else if (c == ' ')
        out = 1;
    return (out);
}

int     ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

unsigned int    ft_atoui(const char *str, int *res_shift)
{
    size_t          i;
    unsigned int    out;
    int             was_num;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    out = 0;
    was_num = 0;
    if (ft_isdigit(str[i]))
        was_num = 1;
    while (ft_isdigit(str[i]))
        out = out * 10 + (str[i++] - '0');
    *res_shift = int_ternary((was_num && (ft_isspace(str[i]) || !str[i]
                    || str[i] == ',')), *res_shift + i, -1);
    return (out);
}

static double   ft_atof2(const char *str, size_t *i, int *was_num)
{
    double  ten;
    double  out;

    out = 0;
    if (str[*i] == '.' && ++(*i))
    {
        ten = 0.1;
        *was_num = int_ternary(ft_isdigit(str[*i]), 1, *was_num);
        while (str[*i] >= '0' && str[*i] <= '9')
        {
            out += (str[(*i)++] - '0') * ten;
            ten /= 10.;
        }
    }
    return (out);
}

double  ft_atof(const char *str, int *res_shift)
{
    size_t  i;
    double  out;
    int     was_num;
    int     sign;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    out = 0;
    sign = 1;
    was_num = 0;
    if (str[i] == '-' && ++i)
        sign = -1;
    was_num = int_ternary(ft_isdigit(str[i]), 1, was_num);
    while (str[i] >= '0' && str[i] <= '9')
        out = out * 10 + (str[i++] - '0');
    out += ft_atof2(str, &i, &was_num);
    *res_shift = int_ternary((was_num && (ft_isspace(str[i])
                    || !str[i] || str[i] == ',')), *res_shift + i, -1);
    return (out * sign);
}
