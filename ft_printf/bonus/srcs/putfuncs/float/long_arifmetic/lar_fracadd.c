#include "long_arifmetic.h"

static size_t	count_digits(const t_long_num *a, const t_long_num *b)
{
	size_t	lim;
	size_t	c;
	size_t	delta;
	int		rem;

	delta = (a->len > b->len) ? (a->len - b->len) : (b->len - a->len);
	lim = MIN(a->len, b->len);
	rem = 0;
	c = 0;
	while (++c <= lim)
		rem = ((a->data[lim - c] - '0') +
				(b->data[lim - c] - '0') + rem) / 10;
	(rem) ? c++ : 0;
	(c == 0) ? c = 1 : 0;
	return (delta + (c - 1));
}

static void		copy_tail(t_long_num *dest, const t_long_num *b, size_t delta)
{
	size_t	i;

	i = 0;
	while (++i <= delta)
		dest->data[dest->len - i] = b->data[b->len - i];
}

static void		add(t_long_num *dest, const t_long_num *a, const t_long_num *b)
{
	size_t	i;
	size_t	lim;
	size_t	delta;
	int		rem;
	int		tmp;

	i = 0;
	rem = 0;
	delta = (a->len > b->len) ? (a->len - b->len) : (b->len - a->len);
	copy_tail(dest, (a->len > b->len) ? a : b, delta);
	lim = MIN(a->len, b->len);
	while (++i <= lim)
	{
		tmp = (a->data[lim - i] - '0') + (b->data[lim - i] - '0') + rem;
		dest->data[dest->len - delta - i] = tmp % 10 + '0';
		rem = tmp / 10;
	}
	(rem) ? dest->data[0] = rem + '0' : 0;
}

t_long_num		*lar_fracadd(t_long_num *a, const t_long_num *b)
{
	t_long_num buf;

	buf.len = count_digits(a, b);
	buf.data = (char *)malloc(sizeof(char) * (buf.len + 1));
	buf.data[buf.len] = '\0';
	add(&buf, a, b);
	free(a->data);
	*a = buf;
	return (a);
}
