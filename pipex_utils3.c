/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:32:01 by slambert          #+#    #+#             */
/*   Updated: 2026/02/09 13:32:22 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_127(char *error_msg, int status, int free_msg)
{
	if (error_msg[0] == '/')
		ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
	else
		ft_putstr_fd("command not found: ", STDERR_FILENO);
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (free_msg)
		free(error_msg);
	exit(status);
}

void	error_126(char *error_msg, int status, int free_msg)
{
	ft_putstr_fd("permission denied: ", STDERR_FILENO);
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	errno = EACCES;
	if (free_msg)
		free(error_msg);
	exit(status);
}
