#include "philo_bonus.h"

static int  ft_isspace(char c)
{
    if (c == ' ' || c == '\f' || c == '\n'
        || c == '\t' || c == '\r' || c == '\v')
        return (1);
    return (0);
}

/*
    little ft_atoi

    Parsing only unsigned integers (!) but still in range of int values.
    Skips spaces in the begin and end of string

    Returns:
        val     --  if str is valid
        -1      --  if str is empty of there is non-space and non-digit symbol
*/
static int  ft_atoi(const char *str)
{
    int     out;

    if (!*str)
        return (-1);
    while (ft_isspace(*str))
        str++;
    out = 0;
    while (*str >= '0' && *str <= '9')
    {
        out = out * 10 + *str - '0';
        str++;
    }
    while (ft_isspace(*str))
        str++;
    if (*str)
        out = -1;
    return (out);
}

int agruments_parser(int argc, char **argv, t_setup *global_setup)
{
    if (argc < 5 || argc > 6)
        return (-1);
    global_setup->num_of_philos = ft_atoi(argv[1]);
    if (global_setup->num_of_philos == -1)
        return (-1);
    global_setup->time_to_die = ft_atoi(argv[2]);
    if (global_setup->time_to_die == -1)
        return (-1);
    global_setup->time_to_eat = ft_atoi(argv[3]);
    if (global_setup->time_to_eat == -1)
        return (-1);
    global_setup->time_to_sleep = ft_atoi(argv[4]);
    if (global_setup->time_to_sleep == -1)
        return (-1);
    if (argc == 6)
    {
        global_setup->required_number_of_meals = ft_atoi(argv[5]);
        if (global_setup->required_number_of_meals == -1)
            return (-1);
    }
    else
        global_setup->required_number_of_meals = -1;
    return (0);
}
