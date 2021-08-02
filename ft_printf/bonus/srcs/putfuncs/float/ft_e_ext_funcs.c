#include "ft_printf.h"

static char	*move_to_int(t_long_num *f_buf, char *i_data_new, int *e)
{
	char	*f_data_new;
	size_t	i;
	size_t	j;

	i = 0;
	i_data_new[0] = '0';
	*e = -1;
	while (f_buf->data[i++] == '0')
		*e -= 1;
	i_data_new[0] = f_buf->data[--i];
	f_data_new = (char *)malloc(sizeof(char) * (f_buf->len - i - 1));
	j = 0;
	while (i + j < f_buf->len)
	{
		f_data_new[j] = f_buf->data[i + 1 + j];
		j++;
	}
	f_buf->len -= i + 1;
	return (f_data_new);
}

static char	*move_to_frac(t_long_num *i_buf, t_long_num *f_buf,
							char *i_data_new, int *e)
{
	char	*f_data_new;
	size_t	i;
	size_t	j;

	i_data_new[0] = i_buf->data[0];
	f_data_new = (char *)malloc(sizeof(char) * (f_buf->len + i_buf->len));
	i = 0;
	while (++i < i_buf->len)
	{
		f_data_new[i - 1] = i_buf->data[i];
		*e += 1;
	}
	j = 0;
	while (j <= f_buf->len)
		f_data_new[i++ - 1] = f_buf->data[j++];
	f_buf->len = f_buf->len + i_buf->len - 1;
	return (f_data_new);
}

int			move_to_sci_form(t_long_num *i_buf, t_long_num *f_buf)
{
	char	*i_data_new;
	char	*f_data_new;
	int		e;

	e = 0;
	i_data_new = (char *)malloc(sizeof(char) * 2);
	i_data_new[1] = '\0';
	if (i_buf->len == 1 && i_buf->data[0] == '0')
		f_data_new = move_to_int(f_buf, i_data_new, &e);
	else
		f_data_new = move_to_frac(i_buf, f_buf, i_data_new, &e);
	free(i_buf->data);
	free(f_buf->data);
	i_buf->data = i_data_new;
	i_buf->len = 1;
	f_buf->data = f_data_new;
	return (e);
}
