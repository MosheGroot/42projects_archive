#include "get_next_line.h"

int     get_next_line(int fd, char **line)
{
    static t_buffer main_buffer[FD_LIM] = {{NULL, 0}};
    t_buffer        tmp_buffer;
    int             st;

    if (get_default_buffers(main_buffer + fd, &tmp_buffer) == -1)
        return (-1);
    st = 0;
    if (!line || fd < 0 || fd > FD_LIM || (read(fd, tmp_buffer.data, 0) == -1))
        st = -1;
    else if (main_buffer[fd].data && main_buffer[fd].data[0]
        && complete_line(line, main_buffer + fd, -1))
        st = 1;
    if (st == 0)
        st = read_line(fd, line, main_buffer + fd, &tmp_buffer);
    free(tmp_buffer.data);
    if (st == 0)
    {
        *line =main_buffer[fd].data;
        main_buffer[fd].data = NULL;
        main_buffer[fd].len = 0;
    }
    return (st);
}
