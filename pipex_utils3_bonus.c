/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 13:59:45 by slambert          #+#    #+#             */
/*   Updated: 2025/12/19 14:02:11 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipes[i]) == -1)
			custom_error("pipe returned -1", EXIT_FAILURE);
		i++;
	}
}

// TODO error handling??
void	init_struct(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;

	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd_count = argc - 3;
	pipex->pid = NULL;
	pipex->pipes = NULL;
	pipex->pid = malloc(sizeof(int) * (pipex->cmd_count));
	if (!pipex->pid)
		error_exit("malloc failure in init_struct", 1, pipex);
	pipex->pipes = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (!pipex->pipes)
		error_exit("malloc failure in init_struct", 1, pipex);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
			error_exit("malloc failure in init_struct", 1, pipex);
		i++;
	}
}

void	close_all_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i <= pipex->cmd_count - 2)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}

void	free_stuff(t_pipex *pipex)
{
	int	i;

	free(pipex->pid);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}

int	return_handler(int pid1, int pid2)
{
	int	exit_code;
	int	status;

	exit_code = 0;
	pid1 = wait(&status);
	while (pid1 != -1)
	{
		if (pid1 == pid2)
			exit_code = status;
		pid1 = wait(&status);
	}
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (EXIT_FAILURE);
}
