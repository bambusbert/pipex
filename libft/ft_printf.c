/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:38:27 by slambert          #+#    #+#             */
/*   Updated: 2025/11/10 16:03:37 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	dispatcher(va_list ap, char c);
// int	pointer_handler(va_list ap);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	if (!fmt)
		return (-1);
	if (fmt[0] == '%' && fmt[1] == '\0')
		return (-1);
	va_start(ap, fmt);
	i = 0;
	ret = 0;
	while (fmt[i++])
	{
		if (fmt[i - 1] != '%')
			ret += ft_putchar_fd(fmt[i - 1], 1);
		else
			ret += dispatcher(ap, fmt[i++]);
	}
	va_end(ap);
	return (ret);
}

int	dispatcher(va_list ap, char c)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(ap, char *), 1));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr_fd(va_arg(ap, int), 1));
	else if (c == 'u')
		return (ft_putnbr_fd_unsigned(va_arg(ap, unsigned int), 1));
	else if (c == 'p')
		return (pointer_handler(ap));
	else if (c == 'X')
		return (ft_putnbr_hex(va_arg(ap, unsigned int)));
	else if (c == 'x')
		return (ft_putnbr_hex_lowercase(va_arg(ap, unsigned int)));
	else if (c == '%')
		return (ft_putchar_fd('%', 1));
	else
	{
		ft_putchar_fd('%', 1);
		ft_putchar_fd(c, 1);
		return (2);
	}
}

int	pointer_handler(va_list ap)
{
	unsigned long	pointer_value;

	pointer_value = (unsigned long)va_arg(ap, void *);
	if (pointer_value == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		ft_putstr_fd("0x", 1);
		return (ft_putnbr_hex_pointer(pointer_value) + 2);
	}
}
/* #include <stdio.h>

int	main(void)
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
	ft_putnbr_hex(123456);
	printf("\n");
	ft_putnbr_hex_lowercase(123456);
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
 */