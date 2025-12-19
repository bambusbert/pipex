/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 13:51:50 by slambert          #+#    #+#             */
/*   Updated: 2025/12/19 13:59:10 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	free2d_and_error_exit(char **arr, char *error_msg, int status,
		t_pipex *pipex)
{
	free_2d(arr);
	error_exit(error_msg, status, pipex);
}

void	error_exit(char *error_msg, int status, t_pipex *pipex)
{
	free_stuff(pipex);
	if (status == 127)
		errno = ENOENT;
	else if (status == 126)
		errno = EACCES;
	perror(error_msg);
	exit(status);
}

void	clean_exit(char *msg, int *p_fd, int file_fd, t_pipex *pipex)
{
	if (p_fd)
	{
		close(p_fd[0]);
		close(p_fd[1]);
	}
	if (file_fd != -1)
		close(file_fd);
	free_stuff(pipex);
	perror(msg);
	exit(EXIT_FAILURE);
}

void	custom_error(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(status);
}
