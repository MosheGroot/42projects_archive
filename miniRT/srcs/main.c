#include "parser.h"
#include "window.h"

static int  check_ext(char *filename)
{
    while (*filename && *filename != '.')
        filename++;
    if (*filename != '.')
        return (0);
    filename++;
    if (*filename != 'r')
        return (0);
    filename++;
    if (*filename != 't')
        return (0);
    filename++;
    if (*filename)
        return (0);
    return (1);
}

static t_data   get_empty_data(void)
{
    t_data  out;

    out.frame.res_x = 0;
    out.frame.res_y = 0;
    out.frame.rendered = 0;
    out.frame.zoom = 1.;
    out.frame.curr_cam = NULL;
    out.frame.img = NULL;
    out.frame.curr_cam = NULL;
    out.frame.scene.cams = NULL;
    out.frame.scene.lights = NULL;
    out.frame.scene.objs = NULL;
    out.frame.scene.amb_coeff = 0.;
    out.frame.scene.amb_col.r = 0;
    out.frame.scene.amb_col.g = 0;
    out.frame.scene.amb_col.b = 0;
    out.mlx = NULL;
    out.mlx_win = NULL;
    return (out);
}

static int  ft_strcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return (-1);
    while (*s1 == *s2 && *s1 && *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int     main(int argc, char **argv)
{
    t_data  data;

    if (argc != 2 && argc != 4)
        log_error("Error\nWrong number of arguments! ", EINVAL);
    if (!check_ext(argv[1]))
        log_error("Error\nWrong extension of file! ", EINVAL);
    data = get_empty_data();
    parse_file(argv[1], &data);
    if (argc == 2)
        start_window(&data);
    else if (!ft_strcmp(argv[2], "--save"))
        save_to_file(&data, argv[3]);
    return (0);
}
