#include "long_arifmetic.h"

static size_t	count_digits(const t_long_num *a, const t_long_num *b)
{
	size_t	c;
	int		rem;

	rem = 0;
	c = 0;
	while (++c <= MIN(a->len, b->len))
		rem = ((a->data[a->len - c] - '0') + (b->data[b->len - c] - '0')
				+ rem) / 10;
	if (a->len < b->len)
		a = b;
	while (c <= a->len)
		rem = ((a->data[a->len - c++] - '0') + rem) / 10;
	(rem) ? c++ : 0;
	(c == 0) ? c = 1 : 0;
	return (c - 1);
}

static void		add(t_long_num *dest, const t_long_num *a, const t_long_num *b)
{
	size_t	i;
	int		tmp;
	int		rem;

	i = 0;
	rem = 0;
	while (++i <= MIN(a->len, b->len))
	{
		tmp = (a->data[a->len - i] - '0') + (b->data[b->len - i] - '0') + rem;
		dest->data[dest->len - i] = tmp % 10 + '0';
		rem = tmp / 10;
	}
	(a->len < b->len) ? a = b : 0;
	while (i <= a->len)
	{
		tmp = (a->data[a->len - i] - '0') + rem;
		dest->data[dest->len - i++] = tmp % 10 + '0';
		rem = tmp / 10;
	}
	(rem) ? dest->data[0] = rem + '0' : 0;
}

t_long_num		*lar_add(t_long_num *a, const t_long_num *b)
{
	t_long_num	buf;

	buf.len = count_digits(a, b);
	buf.data = (char *)malloc(sizeof(char) * (buf.len + 1));
	if (!buf.data)
		return (NULL);
	buf.data[buf.len] = '\0';
	add(&buf, a, b);
	free(a->data);
	*a = buf;
	return (a);
}
