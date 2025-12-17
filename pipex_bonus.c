/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:17 by slambert          #+#    #+#             */
/*   Updated: 2025/12/17 18:15:50 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* argv[1] = file1
argv[2] = cmd1
argv[3] = cmd2
argv[4] = file2 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	
	if (argc != 5)
		custom_error("wrong input. Correct Input: ./pipex <file1> <cmd1> <cmd2> ... <cmd_n> <file2>", EXIT_FAILURE);
	init_struct(&pipex, argc, argv, envp);
	if (pipe(pipex.fd) == -1)
		custom_error("pipe returned -1", EXIT_FAILURE);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		clean_exit("first fork failed", pipex.fd, -1);
	if (pipex.pid1 == 0)
		child_cmd_1(&pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		clean_exit("second fork failed", pipex.fd, -1);
	if (pipex.pid2 == 0)
		child_cmd_2(&pipex);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	return return_handler (pipex.pid1, pipex.pid2);
}

void    init_struct (t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
}

int	return_handler(int pid1, int pid2)
{
	int exit_code;
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
	if (pipex->fd_infile  < 0)
		clean_exit("infile error", pipex->fd, -1);
	if (dup2(pipex->fd_infile, STDIN_FILENO) < 0)
		clean_exit("dup2 infile error", pipex->fd, pipex->fd_infile );
	if (dup2(pipex->fd[1], STDOUT_FILENO) < 0)
		clean_exit("dup2 pipe error", pipex->fd, pipex->fd_infile );
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
	pipex->fd_outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_outfile < 0)
		clean_exit("outfile error", pipex->fd, -1);
	if (dup2(pipex->fd[0], STDIN_FILENO) < 0)
		clean_exit("dup2 pipe error", pipex->fd, pipex->fd_outfile);
	if (dup2(pipex->fd_outfile, STDOUT_FILENO) < 0)
		clean_exit("dup2 outfile error", pipex->fd, pipex->fd_outfile);
	close(pipex->fd_outfile);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	do_execve_stuff(pipex->argv[3], pipex->envp);
}

void	error_exit(char *error_msg, int status)
{
	if (status == 127)
		errno = ENOENT;
	else if (status == 126)
		errno = EACCES;
	perror(error_msg);
	exit(status);
}

void	clean_exit(char *msg, int *p_fd, int file_fd)
{
	if (p_fd)
	{
		close(p_fd[0]);
		close(p_fd[1]);
	}
	if (file_fd != -1)
		close(file_fd);
	perror(msg);
	exit(EXIT_FAILURE);
}

void custom_error (char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(status);
}