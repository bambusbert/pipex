#include "libft.h"

int main(void)
{
    const char	*p = "%d%d%d";
	char		str[] = "fbnshbvqe";

	// printf("%d\n", ft_printf("%p", 0));
	// printf("%d\n", printf("%p", 0));
	// printf("OG %d\n", printf("%"));
	// printf("MY %d\n", ft_printf("%"));
	// printf("OG\n");
	// ft_printf("%");
	// printf("MY\n");
	// ft_printf("%");
	//printf("arguments: %d\n", count_args(p));
	ft_printf("asd%ifg%ih", 5, 4);
	ft_printf("%i%c%i%i%i\n", 1, 'd', 2, 3, 4);
	printf("%p\n", p);
	ft_printf("%p\n", p);
	printf("OG %s\n", str);
	ft_printf("MY %s\n", str);
	printf("OG %d\n", -10);
	ft_printf("MY %d\n", -10);
	printf("OG %p\n", p);
	ft_printf("MY %p\n", p);
	printf("OG %X\n", 1234);
	ft_printf("MY %X\n", 1234);
	// printf("OG %k\n", 1234);
	// ft_printf("MY %k\n", 1234);
	printf("OG %x\n", 255);
	ft_printf("MY %x\n", 255);
	printf("OG %p\n", NULL);
	ft_printf("MY %p\n", NULL);
	printf("OG: Pointer: %p\n", &str);
	ft_printf("MY: Pointer: %p\n", &str);
	// printf("OG: HEX: %X\n", &str);
	// ft_printf("MY: HEX: %X\n", &str);
	printf("OG: %x\n", 0);
	ft_printf("MY: %x\n", 0);
	// printf("OG: %7\n", 0);
	// ft_printf("MY: %7\n", 0);
	// printf("OG: %\n");
	// ft_printf("MY: %\n");
	// printf("OG: %\n");
	// ft_printf("MY: %\n");
}