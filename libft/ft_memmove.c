/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:19 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 15:56:54 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	i = 0;
	if (pdest < psrc)
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	else
	{
		while (i++ < n)
			pdest[n - i] = psrc[n - i];
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char buf1[20] = "123456789";
	char buf2[20] = "123456789";

	// Test 1: non-overlapping
	ft_memmove(buf1, "abcdef", 5);
	memmove(buf2, "abcdef", 5);
	printf("Test 1: %s\n", strcmp(buf1, buf2) == 0 ? "PASS" : "FAIL");

	// Test 2: overlapping forward (dest < src)
	char buf3[20] = "123456789";
	char buf4[20] = "123456789";
	ft_memmove(buf3, buf3 + 2, 5);
	memmove(buf4, buf4 + 2, 5);
	printf("Test 2: %s\n", strcmp(buf3, buf4) == 0 ? "PASS" : "FAIL");

	// Test 3: overlapping backward (dest > src)
	char buf5[20] = "123456789";
	char buf6[20] = "123456789";
	ft_memmove(buf5 + 2, buf5, 5);
	memmove(buf6 + 2, buf6, 5);
	printf("Test 3: %s\n", strcmp(buf5, buf6) == 0 ? "PASS" : "FAIL");

	return (0);
} */
