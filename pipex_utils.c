/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:33 by slambert          #+#    #+#             */
/*   Updated: 2025/12/11 19:23:59 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void do_execve_stuff(char *str, char** envp)
{
/*     execve needs 3 variables, 
    var1:  char* path
    var2: char* argv[]
        argv[0]: command (e.g. grep)
        argv[1]: flag 1
        argv[2]: flag 2*
        argv[n]: flag n
        argv[n+1]: NULL
    var3: envp: ???*/
    char *path;
    char **strs;
    strs = ft_split(str, ' ');
    path = strs[0]; //TODO add path before
    strs++;
    execve(path, strs, envp);
}

/* char    *substr_until_char(char *s, char c)
{
    char *pos = ft_strchr(s, c);
    if (!pos)
        return (s);
    return ft_substr(s, 0, pos - s);
}

char    *substr_char_until_end(char *s, char c)
{
    char *pos = ft_strchr(s, c);
    if (!pos)
        return (NULL);
    return ft_substr(s, pos - s + 1, ft_strlen(s));
}

int main (void)
{
    char *str = "hallo 12";

    printf("erster teil: %s\n", substr_until_char(str, ' '));
    printf("zweiter teil: %s\n", substr_char_until_end(str, ' '));
}
 */