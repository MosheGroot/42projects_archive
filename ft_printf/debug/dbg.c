#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>
#include <float.h>
#include <string.h>

int		main(void)
{
	printf("  [%d]\n", printf("[% 5d]", 10));
	printf("  [%d]\n", ft_printf("[% 5d]", 10));
	printf("  [%d]\n", printf("[%#50.12f]", 10.123));
	printf("  [%d]\n", ft_printf("[%#50.12f]", 10.123));
	printf("  [%d]\n", printf("[%#20.12e]", 10.123));
	printf("  [%d]\n", ft_printf("[%#20.12e]", 10.123));
	return (0);
}
