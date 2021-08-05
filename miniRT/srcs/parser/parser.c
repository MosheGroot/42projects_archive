#include "parser.h"

static int  ft_strncmp(const char *s1, const char *s2, int len)
{
    while (*s1 == *s2)
    {
        s1++;
        s2++;
        len--;
    }
    return (int_ternary((len > 0), (*s2 - *s1), 0));
}

static int  parse_command2(char *command, t_frame *data)
{
    int     shift;

    shift = -1;
    if (*command == '\0')
        shift = 0;
    else if (!ft_strncmp(command, "sp", 2))
        shift = parse_sphere(command, &data->scene);
    else if (!ft_strncmp(command, "pl", 2))
        shift = parse_plane(command, &data->scene);
    else if (!ft_strncmp(command, "sq", 2))
        shift = parse_square(command, &data->scene);
    else if (!ft_strncmp(command, "tr", 2))
        shift = parse_triangle(command, &data->scene);
    else if (!ft_strncmp(command, "cy", 2))
        shift = parse_cylinder(command, &data->scene);
    else if (command[0] == 'R')
        shift = parse_resolution(command, data);
    else if (command[0] == 'A')
        shift = parse_ambient_light(command, &data->scene);
    else if (command[0] == 'c')
        shift = parse_camera(command, &data->scene);
    else if (command[0] == 'l')
        shift = parse_light(command, &data->scene);
    return (shift);
}

int     parse_command(char *command, t_frame *data)
{
    int     shift;

    while (ft_isspace(*command))
        command++;
    if (*command == '#')
        return (0);
    shift = parse_command2(command, data);
    while (shift > 0 && ft_isspace(command[shift]))
        shift++;
    if (command[shift] != '\0' && command[shift] != '#')
        shift = -1;
    return (int_ternary((shift == -1), -1, 0));
}

void    check_p_status(int p_status, char *command, int fd, t_data *data)
{
    if (p_status == -1 || p_status == -2)
    {
        printf("%s\n", command);
        close(fd);
        emergency_quit(0, p_status, &data->frame.scene);
    }    
}

void    parse_file(char *filename, t_data *data)
{
    int     fd;
    int     r_status;
    int     p_status;
    char    *command;

    if (int_assigment(&fd, open(filename, O_RDONLY)) < 0)
        log_errno("Error\nCan't open the scene! ");
    while (1)
    {
        r_status = get_next_line(fd, &command);
        if (r_status == -1)
            break ;
        p_status = parse_command(command, &data->frame);
        free(command);
        check_p_status(p_status, command, fd, data);
        if (r_status == 0)
            break ;
    }
    close(fd);
    if (r_status == -1)
        emergency_quit(r_status, p_status, &data->frame.scene);
    lst_convert_to_cycle(data->frame.scene.cams);
}
