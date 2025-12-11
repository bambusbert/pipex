/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:18:30 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 15:55:29 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}
/*
#include <stdio.h>

int main (void)
{
	char c = 262;
	int x = ft_isalnum(c);
	int y = isalnum(c);
	printf("MY VERSION: %d\n", x);
	printf("OG VERSION: %d\n", y);
} */