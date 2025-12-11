/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:31 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 15:58:43 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	return (NULL);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[] = "asdfghjkaaaaaaaaa";
	int c = '\0';

	printf("%d MY VERSION\n", ft_strrchr(str, c));
	printf("%d OG VERSION\n", strrchr(str, c));
}  */