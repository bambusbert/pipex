/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:33 by slambert          #+#    #+#             */
/*   Updated: 2025/12/19 13:58:09 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
void	do_execve_stuff(char *str, char **envp, t_pipex *pipex)
{
	char	*path_var;
	char	*path;
	char	**strs;

	path_var = extract_pathvar_from_envp(envp);
	strs = ft_split(str, ' ');
	if (!strs[0])
	{
		free_2d(strs);
		error_exit("command not found", 127, pipex);
	}
	path = extract_path_from_pathvar(path_var, strs, pipex);
	if (!path)
	{
		free_2d(strs);
		error_exit("Error in do_execve_stuff", 127, pipex);
	}
	execve(path, strs, envp);
	free(path);
	free_2d(strs);
	error_exit("execve failed", 1, pipex);
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
char	*extract_path_from_pathvar(char *path_var, char **strs, t_pipex *pipex)
{
	char	**paths;
	char	*checked_path;
	int		i;

	if (ft_strchr(strs[0], '/'))
		return (absolute_path_helper(strs, pipex));
	if (path_var == NULL)
		free2d_and_error_exit(strs, "command not found", 127, pipex);
	paths = ft_split(path_var, ':');
	if (!paths)
		free2d_and_error_exit(strs, "error in extract_path_from_pathvar, \
			ft_split failed", EXIT_FAILURE, pipex);
	i = 0;
	while (paths[i])
	{
		checked_path = check_single_path(paths[i], paths, strs[0], pipex);
		if (checked_path)
			return (checked_path);
		i++;
	}
	free_2d(paths);
	free2d_and_error_exit(strs, "command not found", 127, pipex);
	return (NULL);
}

char	*absolute_path_helper(char **strs, t_pipex *pipex)
{
	if (access(strs[0], F_OK) == -1)
	{
		free_2d(strs);
		error_exit("command not found", 127, pipex);
	}
	if (access(strs[0], X_OK) == -1)
	{
		free_2d(strs);
		error_exit("command not executable", 126, pipex);
	}
	return (ft_strdup(strs[0]));
}

char	*check_single_path(char *path, char **paths, char *cmd, t_pipex *pipex)
{
	char	*path_with_slash;
	char	*path_to_check;

	path_with_slash = ft_strjoin(path, "/");
	if (!path_with_slash)
	{
		free_2d(paths);
		error_exit("error in extract_path_from_pathvar, ft_strjoin failed",
			EXIT_FAILURE, pipex);
	}
	path_to_check = ft_strjoin(path_with_slash, cmd);
	free(path_with_slash);
	if (!path_to_check)
	{
		free_2d(paths);
		error_exit("error in extract_path_from_pathvar, ft_strjoin failed",
			EXIT_FAILURE, pipex);
	}
	if (access(path_to_check, X_OK) == 0)
	{
		free_2d(paths);
		return (path_to_check);
	}
	free(path_to_check);
	return (NULL);
}
