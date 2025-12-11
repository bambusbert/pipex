/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:45 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 13:05:19 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;

	p = NULL;
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			p = (char *)&s[i];
			return (p);
		}
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (p);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[] = "teste";
	int c = '\0'; // a

	printf("%d MY VERSION\n", ft_strchr(str, c));
	printf("%d OG VERSION\n", strchr(str, c));
} */