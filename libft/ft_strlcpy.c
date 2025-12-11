/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:11 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 12:38:33 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
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
	printf ("dest before: %s\n", dest1);
	i = ft_strlcpy(dest1, src1, 4);
	printf ("dest after: %s\n", dest1);
	printf ("%d\n", i);
	printf("OG VERSION\n");
	printf ("dest before: %s\n", dest2);
	i = strlcpy(dest2, src2, 4);
	printf ("dest after: %s\n", dest2);
	printf ("%d\n", i);
	return (0);
}
 */