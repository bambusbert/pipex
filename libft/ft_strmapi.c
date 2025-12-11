/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:21 by slambert          #+#    #+#             */
/*   Updated: 2025/10/07 14:20:22 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	my_test_func(unsigned int i, char c);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*p;

	len = ft_strlen(s);
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "asdf";
	char	*p;

	p = ft_strmapi(str, my_test_func);
	printf("%s\n", p);
	free (p);
}

char	my_test_func(unsigned int i, char c)
{
	return (c + i);
}


char	my_test_func3(unsigned int i, char c)
{
	return (c - i);
} */