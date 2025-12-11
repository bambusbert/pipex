/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:37 by slambert          #+#    #+#             */
/*   Updated: 2025/10/09 11:32:45 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	should_be_removed(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (ft_calloc(1, 1));
	start = 0;
	while (s1[start] && should_be_removed(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && should_be_removed(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, end - start));
}
/*
#include <stdio.h>

int	main(void)
{
	char s1[] = "  ghdsgs<  ";
	char set[] = " ";
	char *p;
	p = ft_strtrim(s1, set);
	printf("%s\n", p);
} */