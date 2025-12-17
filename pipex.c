/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:17 by slambert          #+#    #+#             */
/*   Updated: 2025/12/17 14:40:55 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* argv[1] = file1
argv[2] = cmd1
argv[3] = cmd2
argv[4] = file2 */
int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	status;

	if (argc != 5)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		clean_exit("first fork failed", fd, -1);
	if (pid1 == 0)
		child_cmd_1(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		clean_exit("second fork failed", fd, -1);
	if (pid2 == 0)
		child_cmd_2(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
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
void	child_cmd_1(int *fd, char **argv, char **envp)
{
	int	file;

	file = open(argv[1], O_RDONLY);
	if (file < 0)
		clean_exit("infile error", fd, -1);
	if (dup2(file, STDIN_FILENO) < 0)
		clean_exit("dup2 infile error", fd, file);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		clean_exit("dup2 pipe error", fd, file);
	close(file);
	close(fd[0]);
	close(fd[1]);
	do_execve_stuff(argv[2], envp);
}

/* child process 2 - cmd2
close writing end of pipe
0. open outfile
1. redirect standard input of cmd2 to the read end of the pipe
2. redirect standard output to the fd of file2
3. execute cmd2 (execve)
4. close outfile
X. close fds that are not used and pipe ends */
void	child_cmd_2(int *fd, char **argv, char **envp)
{
	int	file;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
		clean_exit("outfile error", fd, -1);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		clean_exit("dup2 pipe error", fd, file);
	if (dup2(file, STDOUT_FILENO) < 0)
		clean_exit("dup2 outfile error", fd, file);
	close(file);
	close(fd[0]);
	close(fd[1]);
	do_execve_stuff(argv[3], envp);
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
