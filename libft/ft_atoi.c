/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:16:08 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 16:07:00 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*shift_whitespace(const char *nptr);
static int			sign_handler(const char *nptr);

int	ft_atoi(const char *nptr)
{
	int			i;
	long long	num;
	int			minus;

	if (!nptr)
		return (0);
	nptr = shift_whitespace(nptr);
	minus = sign_handler(nptr);
	if (minus == -1)
		return (0);
	if (minus == 2 || minus == 3)
		nptr++;
	num = 0;
	i = 0;
	while (nptr[i])
	{
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			break ;
		num *= 10;
		num += nptr[i] - 48;
		i++;
	}
	if (minus == 3)
		num *= (-1);
	return ((int)num);
}

static int	sign_handler(const char *nptr)
{
	int	minus;
	int	was_there_a_sign;

	if (*nptr >= '0' && *nptr <= '9')
		return (0);
	was_there_a_sign = 0;
	minus = 0;
	if (nptr[0] == '-')
	{
		minus = 1;
		was_there_a_sign = 2;
	}
	else if (nptr[0] == '+')
	{
		was_there_a_sign = 2;
	}
	return (minus + was_there_a_sign);
}

static const char	*shift_whitespace(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\v'
		|| nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	return (&nptr[i]);
}
/* 
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	const char *tests[] = {
		"42",
		"   42",
		"-42",
		"+42",
		"2147483647",  // INT_MAX
		"2147483648",  // INT_MAX + 1
		"-2147483648", // INT_MIN
		"   -123abc",
		"0",
		"  +0",
		"  -0",
		"   ",
		"--42",
		"++42",
		"-+42",
		"+   -42   ",
		"+-42 -",
		"+-42  sda",
		"+ - 42",
		" +- 42",
		"",
		"     + 415",
		"+    415",
		"\t\v\f\r\n \f+\t\v\f\r\n \f1234",
		"+\t\v\f\r\n \f1234"
	};

	int n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++)
	{
		int ft = ft_atoi(tests[i]);
		int og = atoi(tests[i]);
		printf("Test %-20s | ft_atoi: %20d | atoi: %20d | %s\n", tests[i], ft,
			og, (ft == og ? "PASS" : "FAIL"));
	}

	return (0);
} */