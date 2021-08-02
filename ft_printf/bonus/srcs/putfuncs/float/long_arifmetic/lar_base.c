#include "long_arifmetic.h"

t_long_num		*lar_sizeinc(t_long_num *num, size_t delta)
{
	t_long_num	new;
	size_t		i;

	new.len = num->len + delta;
	if (!(new.data = (char *)malloc(sizeof(char) * (new.len + 1))))
		return (NULL);
	new.data[new.len] = '\0';
	i = 0;
	while (++i <= new.len)
		new.data[new.len - i] = num->data[num->len - i];
	while (i <= new.len)
		new.data[new.len - i++] = '0';
	free(num->data);
	*num = new;
	return (num);
}

static size_t	lar_count_digits(unsigned long long num)
{
	size_t	count;

	count = 1;
	while (num /= 10)
		count++;
	return (count);
}

t_long_num		lar_getnum(unsigned long long num)
{
	t_long_num	out;
	size_t		i;

	out.len = lar_count_digits(num);
	out.data = (char *)malloc(sizeof(char) * (out.len + 1));
	if (!out.data)
		return (out);
	out.data[out.len] = '\0';
	i = 0;
	while (++i <= out.len)
	{
		out.data[out.len - i] = num % 10 + '0';
		num /= 10;
	}
	return (out);
}
