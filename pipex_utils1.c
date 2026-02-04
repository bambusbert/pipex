/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:33 by slambert          #+#    #+#             */
/*   Updated: 2026/02/04 17:34:27 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (!strs)
		error_exit("Error DEFINE BETTER", EXIT_FAILURE, 0);
	if (!strs[0])
		free2d_and_error_exit(strs, "", 127);
	path = extract_path_from_pathvar(path_var, strs);
	if (!path)
		free2d_and_error_exit(strs, "Error in do_execve_stuff", 127);
	execve(path, strs, envp);
	free(path);
	free2d_and_error_exit(strs, "execve failed", 1);
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
	if (path_var == NULL)
		free2d_and_error_exit(strs, strs[0], 127);
	paths = ft_split(path_var, ':');
	if (!paths)
		free2d_and_error_exit(strs,
			"error in extract_path_from_pathvar, \
			ft_split failed", EXIT_FAILURE);
	i = -1;
	while (paths[++i])
	{
		checked_path = check_single_path(paths[i], paths, strs[0]);
		if (checked_path)
			return (checked_path);
	}
	free_2d(paths);
	free2d_and_error_exit(strs, strs[0], 127);
	return (NULL);
}

void	free2d_and_error_exit(char **arr, char *error_msg, int status)
{
	char *copy = ft_strdup(error_msg);
	if (!copy)
		error_exit("Malloc Failure inside free2d_and_error_exit", EXIT_FAILURE, 0);
	free_2d(arr);
	error_exit(copy, status, 1);
}

char	*absolute_path_helper(char **strs)
{
	if (access(strs[0], F_OK) == -1)
		free2d_and_error_exit(strs, strs[0], 127);
	if (access(strs[0], X_OK) == -1)
		free2d_and_error_exit(strs, strs[0], 126);
	return (ft_strdup(strs[0]));
}

char	*check_single_path(char *path, char **paths, char *cmd)
{
	char	*path_with_slash;
	char	*path_to_check;

	path_with_slash = ft_strjoin(path, "/");
	if (!path_with_slash)
		free2d_and_error_exit(paths, "error in extract_path_from_pathvar, \
			ft_strjoin failed", EXIT_FAILURE);
	path_to_check = ft_strjoin(path_with_slash, cmd);
	free(path_with_slash);
	if (!path_to_check)
		free2d_and_error_exit(paths,
			"error in extract_path_from_pathvar,\
			ft_strjoin failed", EXIT_FAILURE);
	if (access(path_to_check, X_OK) == 0)
	{
		free_2d(paths);
		return (path_to_check);
	}
	free(path_to_check);
	return (NULL);
}
