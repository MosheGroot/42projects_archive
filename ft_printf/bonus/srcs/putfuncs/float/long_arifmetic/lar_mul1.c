#include "long_arifmetic.h"
#include <stdio.h>

static t_long_num	sum_of_rows(t_long_num *bufs, size_t size)
{
	t_long_num	out_buf;
	size_t		i;

	out_buf = lar_getnum(0);
	i = 0;
	while (i < size)
		lar_add(&out_buf, bufs + (i++));
	return (out_buf);
}

static void			*free_bufs(t_long_num *bufs, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(bufs[i++].data);
	free(bufs);
	return (NULL);
}

t_long_num			*lar_mul(t_long_num *a, const t_long_num *b)
{
	t_long_num	*bufs;
	t_long_num	out_buf;
	size_t		i;

	if (!(bufs = (t_long_num *)malloc(sizeof(t_long_num) * b->len)))
		return (NULL);
	i = 0;
	while (i < b->len)
	{
		if (!(bufs[i] = lar_mul_lambda(a, b->data[b->len - 1 - i] - '0')).data)
			return (free_bufs(bufs, i + 1));
		if (!lar_mul_10(bufs + i, i)->data)
			return (free_bufs(bufs, i + 1));
		i++;
	}
	if (!(out_buf = sum_of_rows(bufs, b->len)).data)
		return (free_bufs(bufs, b->len));
	free_bufs(bufs, b->len);
	free(a->data);
	*a = out_buf;
	return (a);
}
