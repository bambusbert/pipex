/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:17 by slambert          #+#    #+#             */
/*   Updated: 2026/02/09 12:57:13 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* argv[1] = file1
argv[2] = cmd1
argv[3] = cmd2
argv[4] = file2 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		custom_error("wrong input . Correct Input: ./pipex <file1> \
			 <cmd1> <cmd2> ... <cmd_n> <file2>", EXIT_FAILURE);
	init_struct(&pipex, argc, argv, envp);
	if (pipe(pipex.fd) == -1)
		clean_exit2("pipe returned -1", NULL, pipex.fd, 1);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		clean_exit2("first fork failed", NULL, pipex.fd, 1);
	if (pipex.pid1 == 0)
		child_cmd_1(&pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		clean_exit2("second fork failed", NULL, pipex.fd, 1);
	if (pipex.pid2 == 0)
		child_cmd_2(&pipex);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	return (return_handler(pipex.pid1, pipex.pid2));
}

/* child process 1, cmd1
-1. close reading end of pipe
0. open infile
1. redirect standard input to fd pointing to file1
2. redirect output of cmd1 into the write end of the pipe
to test if that stuff works just comment out this line (output goes into stdout)
3. execute cmd1 (execve)
4. close infile
X. close fds that are not used and pipe ends */
void	child_cmd_1(t_pipex *pipex)
{
	pipex->fd_infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd_infile < 0)
	{
		if (errno == EISDIR)
			clean_exit2("is a directory", pipex->argv[1], pipex->fd, -1);
		if (errno == EACCES)
			clean_exit2("permission denied", pipex->argv[1], pipex->fd, -1);
		clean_exit2("no such file or directory", pipex->argv[1], pipex->fd, -1);
	}
	if (dup2(pipex->fd_infile, STDIN_FILENO) < 0)
		clean_exit2("dup2 infile error", NULL, pipex->fd, pipex->fd_infile);
	if (dup2(pipex->fd[1], STDOUT_FILENO) < 0)
		clean_exit2("dup2 pipe error", NULL, pipex->fd, pipex->fd_infile);
	close(pipex->fd_infile);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	do_execve_stuff(pipex->argv[2], pipex->envp);
}

/* child process 2 - cmd2
close writing end of pipe
0. open outfile
1. redirect standard input of cmd2 to the read end of the pipe
2. redirect standard output to the fd of file2
3. execute cmd2 (execve)
4. close outfile
X. close fds that are not used and pipe ends */
void	child_cmd_2(t_pipex *pipex)
{
	pipex->fd_outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (pipex->fd_outfile < 0)
	{
		if (errno == EISDIR)
			clean_exit2("is a directory", pipex->argv[4], pipex->fd, -1);
		if (errno == EACCES)
			clean_exit2("permission denied", pipex->argv[4], pipex->fd, -1);
		clean_exit2("no such file or directory", pipex->argv[4], pipex->fd, -1);
	}
	if (dup2(pipex->fd[0], STDIN_FILENO) < 0)
		clean_exit2("dup2 pipe error", NULL, pipex->fd, pipex->fd_outfile);
	if (dup2(pipex->fd_outfile, STDOUT_FILENO) < 0)
		clean_exit2("dup2 outfile error", NULL, pipex->fd, pipex->fd_outfile);
	close(pipex->fd_outfile);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	do_execve_stuff(pipex->argv[3], pipex->envp);
}

//error message for 127 is "command not found: " or "no such file or directory: "
void	error_exit(char *error_msg, int status, int free_msg)
{
	if (status == 127)
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
	if (status == 126)
	{
		ft_putstr_fd("permission denied: ", STDERR_FILENO);
		if (error_msg)
			ft_putstr_fd(error_msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		errno = EACCES;
		exit (status);
	}
	perror(error_msg);
	if (free_msg)
		free(error_msg);
	exit(status);
}

void	clean_exit2(char *base_msg, char *detail, int *p_fd, int file_fd)
{
	if (p_fd)
	{
		if (p_fd[0] != -1)
			close(p_fd[0]);
		if (p_fd[1] != -1)
			close(p_fd[1]);
	}
	if (file_fd != -1)
		close(file_fd);
	ft_putstr_fd(base_msg,STDERR_FILENO);
	if (detail)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(detail, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
