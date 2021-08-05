#include "parser.h"

void    emergency_quit(int r_status, int p_status, t_scene *data)
{
    if (data->cams)
        lst_delete(&(data->cams), free);
    if (data->lights)
        lst_delete(&(data->cams), free);
    if (data->cams)
        lst_delete(&(data->cams), free);
    if (r_status == -1)
        log_errno("Error\nCan't read from file! GNL error... ");
    if (p_status == -1)
        log_error("Error\n[SYNTAX_ERROR] ", EINVAL);
    else
        log_errno("Error\nSome sytem error occured! ");
}

int     emergency_return_n_free(void *to_free, int code)
{
    free(to_free);
    return (code);
}

int     parse_resolution(char *command, t_frame *data)
{
    size_t  shift;
    int     delta;

    shift = 1;
    delta = get_t_uinteger(&(data->res_x), command + shift);
    if (delta == -1)
        return (-1);
    shift += delta;
    delta = get_t_uinteger(&(data->res_y), command + shift);
    if (delta == -1)
        return (-1);
    shift += delta;
    if (data->res_x * data->res_y == 0)
        return (-1);
    return (shift);
}

int     parse_ambient_light(char *command, t_scene *data)
{
    size_t  shift;
    int     delta;

    shift = 1;
    delta = get_float(&(data->amb_coeff), command + shift);
    if (delta == -1)
        return (-1);
    shift += delta;
    delta = get_3t_uinteger(&(data->amb_col.r), &(data->amb_col.g),
            &(data->amb_col.b), command + shift);
    if (delta == -1)
        return (-1);
    shift += delta;
    return (shift);
}

int     parse_light(char *comm, t_scene *data)
{
    t_light *l;
    t_list  *to_push;
    size_t  sh;
    int delta;

    sh = 1;
    if (!void_ptr_assigment((void **)&l, malloc(sizeof(t_light))))
        return (-2);
    delta = get_3float(&(l->pos.x), &(l->pos.y), &(l->pos.z), comm + sh);
    if (delta == -1)
        return (emergency_return_n_free((void *)l, -1));
    sh += delta;
    delta = get_float(&(l->br), comm + sh);
    if (delta == -1)
        return (emergency_return_n_free((void *)l, -1));
    sh += delta;
    delta = get_3t_uinteger(&(l->col.r), &(l->col.g), &(l->col.b), comm + sh);
    if (delta == -1)
        return (emergency_return_n_free((void *)l, -1));
    sh += delta;
    if (!void_ptr_assigment((void **)&to_push, (void *)lst_new((void *)l)))
        return (emergency_return_n_free((void *)l, -2));
    lst_push_front(&(data->lights), to_push);
    return (sh);
}
