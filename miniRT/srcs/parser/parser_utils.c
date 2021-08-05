#include "parser.h"

int     get_t_uinteger(unsigned int *num, char *command)
{
    int     shift;

    shift = 0;
    *num = ft_atoui(command, &shift);
    if (shift == -1 || command[shift] == ',')
        return (-1);
    return (shift);
}

int     get_3t_uinteger(unsigned int *a, unsigned int *b, unsigned int *c,
                        char *command)
{
    int     shift;

    shift = 0;
    *a = ft_atoui(command + shift, &shift);
    if (shift == -1 || command[shift] != ',')
        return (-1);
    shift++;
    *b = ft_atoui(command + shift, &shift);
    if (shift == -1 || command[shift] != ',')
        return (-1);
    shift++;
    *c = ft_atoui(command + shift, &shift);
    if (shift == -1 || command[shift] == ',')
        return (-1);
    return (shift);
}

int     get_float(double *num, char *command)
{
    int     shift;

    shift = 0;
    *num = ft_atof(command, &shift);
    if (shift == -1 || command[shift] == ',')
        return (-1);
    return (shift);
}

int     get_3float(double *a, double *b, double *c, char *command)
{
    int     shift;

    shift = 0;
    *a = ft_atof(command + shift, &shift);
    if (shift == -1 || command[shift] != ',')
        return (-1);
    shift++;
    *b = ft_atof(command + shift, &shift);
    if (shift == -1 || command[shift] != ',')
        return (-1);
    shift++;
    *c = ft_atof(command + shift, &shift);
    if (shift == -1 || command[shift] == ',')
        return (-1);
    return (shift);
}
