/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:52 by slambert          #+#    #+#             */
/*   Updated: 2025/10/07 14:19:53 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	my_test_func2(unsigned int i, char *p);

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "asdf";

	printf("%s\n", str);
	ft_striteri(str, my_test_func2);
	printf("%s\n", str);
}

void	my_test_func2(unsigned int i, char *p)
{
	*p = *p + i;
} */