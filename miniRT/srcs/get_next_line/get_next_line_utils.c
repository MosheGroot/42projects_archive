#include "get_next_line.h"

char    *ft_bufcat(t_buffer *b1, const t_buffer *b2)
{
    char    *tmp;
    size_t  index;

    tmp = malloc(sizeof(char) * (b1->len + b2->len + 1));
    if (!tmp)
        return (NULL);
    index = 0;
    while (b1->data && index++ < b1->len)
        tmp[index - 1] = b1->data[index - 1];
    index = 0;
    while (b2->data && index++ < b2->len)
        tmp[b1->len + index - 1] = b2->data[index - 1];
    tmp[b1->len + b2->len] = '\0';
    if (b1->data)
        free(b1->data);
    b1->len += b2->len;
    b1->data = tmp;
    return (tmp);
}

char    *ft_strldup(const char *str, ssize_t len)
{
    char    *out;

    out = (char *)malloc(sizeof(char) * (len + 1));
    if (!out)
        return (NULL);
    out[len] = '\0';
    while (len--)
        out[len] = str[len];
    return (out);
}

int     complete_line(char **line, t_buffer *buffer, ssize_t nl_index)
{
    char    *tmp;

    if (nl_index == -1)
    {
        while (buffer->data[++nl_index] != '\n' && buffer->data[nl_index])
            ;
        if ((size_t)nl_index == buffer->len)
            return (0);
    }
    *line = ft_strldup(buffer->data, nl_index);
    if (!(*line))
        return (-1);
    tmp = ft_strldup(buffer->data + nl_index + 1, buffer->len - nl_index - 1);
    if (!tmp)
        return (-1);
    free(buffer->data);
    buffer->data = tmp;
    buffer->len -= nl_index + 1;
    return (1);
}

int     read_line(int fd, char **line, t_buffer *main_buffer,
                    t_buffer *tmp_buffer)
{
    ssize_t     status;
    ssize_t     nl_index;

    while (1)
    {
        status = read(fd, tmp_buffer->data, BUFFER_SIZE);
        if (status <= 0)
            break ;
        tmp_buffer->data[status] = '\0';
        tmp_buffer->len = status;
        if (!ft_bufcat(main_buffer, tmp_buffer))
            return (-1);
        nl_index = 0;
        while (tmp_buffer->data[nl_index] != '\n' && nl_index < status)
            nl_index++;
        if (nl_index != status)
            return (complete_line(line, main_buffer,
                    main_buffer->len - (status - nl_index)));
    }
    return (0);
}

int     get_default_buffers(t_buffer *main, t_buffer *tmp)
{
    tmp->data = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!tmp->data)
        return (-1);
    tmp->len = 0;
    if (!main->data)
    {
        main->data = (char *)malloc(sizeof(char) * 1);
        if (!main->data)
            return (-1);
        main->data[0] = '\0';
        main->len = 0;
    }
    return (0);
}
