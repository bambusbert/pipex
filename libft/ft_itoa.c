/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:00 by slambert          #+#    #+#             */
/*   Updated: 2025/10/07 15:20:42 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	create_string(char *p, long n, int minus);
static void	reverse_string(char *p, long n, int minus);
static int	calc_digits(long num);
static int	minus_handler(long *nlong);

char	*ft_itoa(int n)
{
	int		i;
	char	*p;
	long	nlong;
	int		minus;

	nlong = n;
	minus = minus_handler(&nlong);
	i = calc_digits(nlong);
	if (!minus)
		p = malloc((i + 1) * sizeof(char));
	else
		p = malloc((i + 2) * sizeof(char));
	if (!p)
		return (NULL);
	create_string(p, nlong, minus);
	reverse_string(p, i, minus);
	if (minus)
		p[i + 1] = '\0';
	else
		p[i] = '\0';
	return (p);
}

static int	minus_handler(long *nlong)
{
	int	minus;

	minus = 0;
	if (*nlong < 0)
	{
		minus = 1;
		*nlong *= -1;
	}
	return (minus);
}

static int	calc_digits(long num)
{
	int	i;

	i = 0;
	while (num > 9)
	{
		num /= 10;
		i++;
	}
	return (i + 1);
}

static void	reverse_string(char *p, long n, int minus)
{
	int		i;
	char	temp;

	if (minus)
		n++;
	i = 0;
	while (i < n / 2)
	{
		temp = p[i];
		p[i] = p[n - 1 - i];
		p[n - 1 - i] = temp;
		i++;
	}
}

static void	create_string(char *p, long n, int minus)
{
	int	i;
	int	res;

	i = 0;
	while (n > 9)
	{
		res = n % 10;
		n /= 10;
		p[i] = res + '0';
		i++;
	}
	p[i] = n + '0';
	if (minus)
	{
		p[i + 1] = '-';
	}
}
/*
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int x = -9;
	char *p;

	p = ft_itoa(x);
	printf("%s\n", p);
} */