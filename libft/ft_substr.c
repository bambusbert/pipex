/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:40 by slambert          #+#    #+#             */
/*   Updated: 2025/12/09 11:00:29 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	p = ft_calloc(1, len + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/* #include "libft.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *s = "HelloWorld";
    struct {
        unsigned int start;
        size_t len;
        const char *expected;
    } tests[] = {
        {0, 5, "Hello"},
        {5, 5, "World"},
        {3, 2, "lo"},
        {8, 10, "ld"},
        {10, 5, ""},
        {20, 3, ""},
        {0, 0, ""}
    };

    int n_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n_tests; i++)
    {
        char *res = ft_substr(s, tests[i].start, tests[i].len);
        printf("Test %d | start=%u len=%zu | got='%s' | expected='%s' | %s\n",
            i + 1, tests[i].start, tests[i].len,
            res, tests[i].expected,
            ft_strncmp(res, tests[i].expected, 50) == 0 ? "PASS" : "FAIL");
        free(res);
    }

    return 0;
}  */