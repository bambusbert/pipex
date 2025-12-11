/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:06 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 16:09:53 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	x;
	size_t	len;

	i = 0;
	x = 0;
	len = 0;
	while (dst[x])
		x++;
	len = x;
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	while (i < size - len - 1 && src[i])
	{
		dst[x] = src[i];
		x++;
		i++;
	}
	if (i <= size - len - 1)
		dst[x] = '\0';
	return (ft_strlen(src) + len);
}
/*
#include <bsd/string.h>
#include <stdio.h>

int main (void)
{
	char	dest1[] = "asdf";
	char	dest2[] = "asdf";
	char	src1[] = "ghjkl";
	char	src2[] = "ghjkl";
	int		i;

	printf("MY VERSION\n");
	printf ("%s\n", dest1);
	i = ft_strlcat(dest1, src1, 15);
	printf ("%s\n", dest1);
	printf ("%d\n", i);
	printf("OG VERSION\n");
	printf ("%s\n", dest2);
	i = strlcat(dest2, src2, 15);
	printf ("%s\n", dest2);
	printf ("%d\n", i);
	return (0);
}
 */