/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:05 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 13:18:43 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	char			*p;
	unsigned char	*buf;

	buf = (unsigned char *)s;
	p = NULL;
	i = 0;
	while (n > 0)
	{
		if ((unsigned char)buf[i] == (unsigned char)c)
		{
			p = (char *)&buf[i];
			return (p);
		}
		i++;
		n--;
	}
	return (p);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str1[] = "sdfajhg";
	int x = 'a';
	printf("%d MY VERSION\n", ft_memchr(str1, x, 4));
	printf("%d OG VERSION\n", memchr(str1, x, 4));
} */