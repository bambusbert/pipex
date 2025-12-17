/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bert <bert@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:33 by slambert          #+#    #+#             */
/*   Updated: 2025/12/17 13:09:50 by bert             ###   ########.fr       */
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
// TODO handle empty command ("")
void	do_execve_stuff(char *str, char **envp)
{
	char	*path_var;
	char	*path;
	char	**strs;

	path_var = extract_pathvar_from_envp(envp);
	strs = ft_split(str, ' ');
	if (!strs[0])
	{
		free_2d(strs);
		error_exit("command not found\n", 127);
	}
	path = extract_path_from_pathvar(path_var, strs);
	if (!path)
	{
		free_2d(strs);
		error_exit("Error in do_execve_stuff\n", 127);
	}
	execve(path, strs, envp);
	free(path);
	free_2d(strs);
	error_exit("execve failed\n", 1);
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
	error_exit("PATH variable not found in ENV variable\n", 127);
	return (NULL);
}

/* this function extracts the correct path from the path vars. the correct path
is the path where a file with the same name as cmd is found */
char	*extract_path_from_pathvar(char *path_var, char **strs)
{
	char	**paths;
	char	*checked_path;
	int		i;

	if (ft_strchr(strs[0], '/'))
		return (absolute_path_helper(strs));
	paths = ft_split(path_var, ':');
	if (!paths)
	{
		free_2d(strs);
		error_exit("error in extract_path_from_pathvar, ft_split failed\n",
			EXIT_FAILURE);
	}
	i = 0;
	while (paths[i])
	{
		checked_path = check_single_path(paths[i], paths, strs[0]);
		if (checked_path)
			return (checked_path);
		i++;
	}
	free_2d(paths);
	free_2d(strs);
	error_exit("command not found\n", 127);
	return (NULL);
}

char	*absolute_path_helper(char **strs)
{
	if (access(strs[0], F_OK) == -1)
	{
		free_2d(strs);
		error_exit("command not found\n", 127);
	}
	if (access(strs[0], X_OK) == -1)
	{
		free_2d(strs);
		error_exit("command not executable\n", 126);
	}
	return (ft_strdup(strs[0]));
}

char	*check_single_path(char *path, char **paths, char *cmd)
{
	char	*path_with_slash;
	char	*path_to_check;

	path_with_slash = ft_strjoin(path, "/");
	if (!path_with_slash)
	{
		free_2d(paths);
		error_exit("error in extract_path_from_pathvar, ft_strjoin failed\n",
			EXIT_FAILURE);
	}
	path_to_check = ft_strjoin(path_with_slash, cmd);
	free(path_with_slash);
	if (!path_to_check)
	{
		free_2d(paths);
		error_exit("error in extract_path_from_pathvar, ft_strjoin failed\n",
			EXIT_FAILURE);
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

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\v')
			i++;
		else
			return (0);
	}
	return (1);
}
