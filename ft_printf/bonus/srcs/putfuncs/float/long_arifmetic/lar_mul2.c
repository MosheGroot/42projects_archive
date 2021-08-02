#include "long_arifmetic.h"

static size_t	count_digits_lambda(const t_long_num *a, int l)
{
	size_t	count;
	int		rem;

	rem = 0;
	count = 0;
	while (++count <= a->len)
		rem = ((a->data[a->len - count] - '0') * l + rem) / 10;
	while (rem)
	{
		rem /= 10;
		count++;
	}
	return (count - 1);
}

t_long_num		*lar_mul_10(t_long_num *a, size_t n)
{
	t_long_num	buf;
	size_t		i;

	buf.len = a->len + n;
	if (!(buf.data = (char *)malloc(sizeof(char) * (buf.len + 1))))
		return (NULL);
	i = -1;
	while (++i < buf.len - n)
		buf.data[i] = a->data[i];
	while (n--)
		buf.data[i++] = '0';
	buf.data[i] = '\0';
	free(a->data);
	*a = buf;
	return (a);
}

t_long_num		lar_mul_lambda(const t_long_num *a, unsigned char l)
{
	t_long_num	out;
	size_t		i;
	int			rem;
	int			tmp;

	out.len = count_digits_lambda(a, l);
	if (!(out.data = (char *)malloc(sizeof(char) * (out.len + 1))))
		return (out);
	out.data[out.len] = '\0';
	i = 0;
	rem = 0;
	while (++i <= a->len)
	{
		tmp = (a->data[a->len - i] - '0') * l + rem;
		out.data[out.len - i] = tmp % 10 + '0';
		rem = tmp / 10;
	}
	if (rem)
		out.data[0] = rem + '0';
	return (out);
}
