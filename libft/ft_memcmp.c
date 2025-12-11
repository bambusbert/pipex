/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:09 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 13:20:04 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;
	size_t			i;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (us1[i] != us2[i])
			return ((unsigned char)us1[i] - (unsigned char)us2[i]);
		i++;
	}
	if (i >= n)
		return (0);
	if (!us1[i] || !us2[i])
		return ((unsigned char)us1[i] - (unsigned char)us2[i]);
	return (0);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str1[] = "asdfjhg";
	char str2[] = "asdf";
	printf("%d MY VERSION\n", ft_memcmp(str1, str2, 4));
	printf("%d OG VERSION\n", memcmp(str1, str2, 4));
} */