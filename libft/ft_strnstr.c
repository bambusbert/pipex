/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:28 by slambert          #+#    #+#             */
/*   Updated: 2025/10/07 14:20:29 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[i])
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && j < ft_strlen(little) && i + j < len)
		{
			j++;
		}
		if (!(j < ft_strlen(little)))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char str1[] = "lorem ipsum dolor sit amet";
	char str2[] = "dolor";
	// char str1[] = "abf abc";
	// char str2[] = "abc";
	// char str1[] = "jdfgfxmsfgsn";
	// char str2[] = "f";
	printf("%s MY VERSION\n", ft_strnstr(str1, str2, 115));
	printf("%s OG VERSION\n", strnstr(str1, str2, 115));
} */