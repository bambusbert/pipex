/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:18:19 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 12:29:34 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>

int main (void)
{
	char buf1[20] = "abcdefghijklmnopqrs";
	printf("String before: '%s'\n", buf1);
	ft_bzero(buf1, 10);
	printf("String after: '%s'\n", buf1);
} */
/* 
int main(void)
{
	//bzero(NULL, 3);
	ft_bzero(NULL, 3);
} */