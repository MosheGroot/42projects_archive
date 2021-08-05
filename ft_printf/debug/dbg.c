#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>
#include <float.h>
#include <string.h>
 
int     main(void)
{
    printf("  [returned : %d]\n", printf("orig: [% 5d]", 10));
    printf("  [returned : %d]\n\n", ft_printf("ft:   [% 5d]", 10));

    printf("  [returned : %d]\n", printf("orig: [%s]", "hello world!"));
    printf("  [returned : %d]\n\n", ft_printf("ft:   [%s]", "hello world!"));

    printf("  [returned : %d]\n", printf("orig: [%-15.9s]", "hello world!"));
    printf("  [returned : %d]\n\n", ft_printf("ft:   [%-15.9s]", "hello world!"));

    printf("  [returned : %d]\n", printf("orig: [%30.12f]", 10.123));
    printf("  [returned : %d]\n\n", ft_printf("ft:   [%30.12f]", 10.123));
    
    printf("  [returned : %d]\n", printf("orig: [%#20.12e]", 10.123));
    printf("  [returned : %d]\n\n", ft_printf("ft:   [%#20.12e]", 10.123));
    
    printf("  [returned : %d]\n", printf("orig: [%p]", "ptr"));
    printf("  [returned : %d]\n\n", ft_printf("ft:   [%p]", "ptr"));

    return (0);
}
