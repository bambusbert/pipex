/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:41 by slambert          #+#    #+#             */
/*   Updated: 2025/10/10 12:50:47 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, size_t len, char c);
static char	*shift_to_next_word(char *s, char c, int skip_start);
static char	*extract_next_word(char const *s, char c);
static char	**free_all(char **strarr, int i);

char	**ft_split(char const *s, char c)
{
	char	**p;
	char	*ss;
	int		word_count;
	int		i;

	word_count = count_words(s, ft_strlen(s), c);
	p = ft_calloc((word_count + 1), sizeof(char *));
	if (!p)
		return (NULL);
	if (word_count == 0)
	{
		p[0] = NULL;
		return (p);
	}
	i = 0;
	ss = shift_to_next_word((char *)s, c, 1);
	while (i++ < word_count)
	{
		p[i - 1] = extract_next_word(ss, c);
		if (!p[i - 1])
			return (free_all(p, i - 1));
		ss = shift_to_next_word(ss, c, 0);
	}
	return (p);
}

static char	*extract_next_word(char const *s, char c)
{
	char	*p;
	int		len;
	int		i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	p = malloc(len * sizeof(char) + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static char	*shift_to_next_word(char *s, char c, int skip_start)
{
	int	i;

	i = 0;
	if (skip_start)
	{
		while (s[i] && s[i] == c)
			i++;
		return (&s[i]);
	}
	while (s[i] && s[i] != c)
		i++;
	while (s[i] && s[i] == c)
		i++;
	return (&s[i]);
}

static int	count_words(char const *s, size_t len, char c)
{
	int		word_count;
	size_t	i;
	int		word;

	word_count = 0;
	word = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] != c && word == 0)
		{
			word_count++;
			word = 1;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return (word_count);
}

//triple pointer wtf
static char	**free_all(char **strarr, int i)
{
	while (i-- > 0)
	{
		free(strarr[i]);
	}
	free(strarr);
	return (NULL);
}
/* 
#include <stdio.h>

int	main(void)
{
	int i = 0;
	int len = 0;
	// char str[] = "hello!";
	// char str[] = "ag,reherhfhjsdgfkhj,asdg,khj,,,,,,,fga,sdhj";
	char str[] = "";
	char **p;

	// char str[] = "";
	p = ft_split(str, ',');
	while (p[i])
	{
		len++;
		i++;
	}
	len--;
	// printf("%d words\n", len);
	i = 0;
	while (i <= len)
	{
		printf("Wort %d: %s\n", i, p[i]);
		i++;
	}
	//extra printf for empty string
	//printf("Wort %d: %s\n", i, p[0]);
	free(p);
} */