/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bert <bert@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:33 by slambert          #+#    #+#             */
/*   Updated: 2025/12/12 18:34:42 by bert             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

/*    
execve needs 3 variables,
var1:  char* path: the path where the specific program is stored
var2: char* argv[]: contains the program to be launched and its flags
    		argv[0]: command (e.g. grep)
	    	argv[1]: flag 1
		    argv[2]: flag 2*
		    argv[n]: flag n
		    argv[n+1]: NULL
var3: envp: thats an array of string pointing to the environment paths.
this variable gets set automatically from main and is passed through*/
void	do_execve_stuff(char *str, char **envp)
{
	char	*path_var;
	char	*path;
	char	**strs;

	path_var = extract_pathvar_from_envp(envp);
	strs = ft_split(str, ' ');
	path = extract_path_from_pathvar(path_var, strs[0]);
	if (!path)
		error_exit("Error\nextract_path_from_pathvar returned NULL", -1);
	dprintf(STDERR_FILENO, "the correct path for '%s' is %s\n", strs[0], path);
	execve(path, strs, envp);
}

char	*extract_pathvar_from_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/* this function extracts the correct path from the path vars. the correct path
is the path where a file with the same name as cmd is found */
char	*extract_path_from_pathvar(char *path_var, char *cmd)
{
	char	**paths;
	char	*checked_path;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = ft_split(path_var, ':');
	if (!paths)
		error_exit("error in extract_path_from_pathvar, ft_split failed", -1);
	i = 0;
	while (paths[i])
	{
		checked_path = check_single_path(paths[i], paths, cmd);
		if (checked_path)
			return (checked_path);
		i++;
	}
	free_2d(paths);
	return (NULL);
}

char	*check_single_path(char *path, char **paths, char *cmd)
{
	char	*path_with_slash;
	char	*path_to_check;

	path_with_slash = ft_strjoin(path, "/");
	if (!path_with_slash)
	{
		free_2d(paths);
		error_exit("error in extract_path_from_pathvar, ft_strjoin failed", -1);
	}
	path_to_check = ft_strjoin(path_with_slash, cmd);
	free(path_with_slash);
	if (!path_to_check)
	{
		free_2d(paths);
		error_exit("error in extract_path_from_pathvar, ft_strjoin failed", -1);
	}
	if (access(path_to_check, X_OK) == 0)
	{
		free_2d(paths);
		return (path_to_check);
	}
	free(path_to_check);
	return (NULL);
}

void	free_2d(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	error_exit(char *error_msg, int status)
{
	// ft_printf("Error\n%s\n", error_msg);
	perror(error_msg);
	exit(status);
}

/* char    *substr_until_char(char *s, char c)
{
	char	*pos;

	pos = ft_strchr(s, c);
	if (!pos)
		return (s);
	return (ft_substr(s, 0, pos - s));
}

char	*substr_char_until_end(char *s, char c)
{
	char	*pos;

	pos = ft_strchr(s, c);
	if (!pos)
		return (NULL);
	return (ft_substr(s, pos - s + 1, ft_strlen(s)));
}

int main (void)
{
	char	*str;

	str = "hallo 12";
	printf("erster teil: %s\n", substr_until_char(str, ' '));
	printf("zweiter teil: %s\n", substr_char_until_end(str, ' '));
}
 */