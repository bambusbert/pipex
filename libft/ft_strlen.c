/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:17 by slambert          #+#    #+#             */
/*   Updated: 2025/12/10 12:31:27 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
/* 
#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[] = "hrsnbth";
	printf("%zu\n", strlen(str));
	printf("%zu\n", ft_strlen(str));
} */