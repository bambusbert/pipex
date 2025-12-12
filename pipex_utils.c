/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:33 by slambert          #+#    #+#             */
/*   Updated: 2025/12/12 14:37:09 by slambert         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"
#include <stdio.h>

void do_execve_stuff(char *str, char** envp)
{
/*     execve needs 3 variables, 
    var1:  char* path: the path where the specific program is stored
    var2: char* argv[]: contains the program to be launched and its flags
        argv[0]: command (e.g. grep)
        argv[1]: flag 1
        argv[2]: flag 2*
        argv[n]: flag n
        argv[n+1]: NULL
    var3: envp: thats an array of string pointing to the environment paths. this variable gets set automatically from main and is passed through*/
    char *path_var;
    char **strs;

    path_var = extract_path_from_envp(envp);
    strs = ft_split(str, ' ');
    dprintf(STDERR_FILENO, "do_execve_stuff: cmd str='%s'\n", str);
    execve(path, strs, envp);
}

char *extract_path_from_envp(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], "PATH=", 5))
            return envp[i] + 5;
        i++;
    }
    return NULL;
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