/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:23 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 12:28:26 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

void	*ft_memset(void *s, int c, size_t n);

int	main(void)
{
	char			buf1[20] = "abcdefghijklmnopqrs";
	char			buf2[20] = "abcdefghijklmnopqrs";
	unsigned char	data1[10];
	unsigned char	data2[10];
	int				identical;

	printf("Before:\n");
	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);
	// Test 1: Fill middle section
	ft_memset(buf1 + 5, 'X', 5);
	memset(buf2 + 5, 'X', 5);
	printf("\nAfter setting 5 bytes to 'X' starting at index 5:\n");
	printf("ft_memset: %s\n", buf1);
	printf("memset   : %s\n", buf2);
	// Test 2: Fill with zeros
	for (int i = 0; i < 10; i++) {
		data1[i] = i + 1;
		data2[i] = i + 1;
	}
	ft_memset(data1, 0, 10);
	memset(data2, 0, 10);
	identical = memcmp(data1, data2, 10) == 0;
	printf("\nBinary test identical: %s\n", identical ? "YES" : "NO");
	return (0);
}
 */
/* 
int main (void)
{
	char *p;
	p = ft_memset(NULL, 99, 4);
	//p = memset(NULL, 99, 4);
} */