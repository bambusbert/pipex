/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:17 by slambert          #+#    #+#             */
/*   Updated: 2025/12/16 12:45:00 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

/* argv[1] = file1
argv[2] = cmd1
argv[3] = cmd2
argv[4] = file2 */
int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	fd_infile;
	int	fd_outfile;
	int	status;

	if (argc != 5)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		error_exit("Error\nfirst fork failed", -1);
	if (pid1 == 0)
		child_cmd_1(fd, &fd_infile, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		error_exit("Error\nsecond fork failed", -1);
	if (pid2 == 0)
		child_cmd_2(fd, &fd_outfile, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	//#define WEXITSTATUS(status) (((status) >> 8) & 0xFF)
	// return (WEXITSTATUS(status));
	// TODO abhängig davon ob gekillt wurde (WIFEXITED):
	/* 		if (WIFEXITED(status)) {
		// Child exited normally (grep with no matches, etc.)
		return (WEXITSTATUS(status));  // Returns 1 for grep no matches
	}
	else if (WIFSIGNALED(status)) {
		// Child was killed by signal (SIGSEGV, SIGKILL, etc.)
		// Shell convention: return 128 + signal number
		return (128 + WTERMSIG(status));
	}
	else {
		// Some other case (stopped, continued, etc.)
		return (1);
	} */
	// return (((status) >> 8) & 0xFF);
	return (WEXITSTATUS(status));
	/* 	in the variable status there are actually 2 things stored
		1. first 0-7 bits: signal number - ONLY IF KILLED
		2. bits 8-31: exit code / signal - if exited normally
		(3. bits 32-64: other stuff like how the process was terminated)
		--> we have to shift bits 8-31 down by 8 bits */
/* 	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		return (128 + WTERMSIG(status)); // Shell convention for signal deaths
	}
	else
	{
		return (1); // Fallback
	} */
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
void	child_cmd_1(int *fd, int *fd_infile, char **argv, char **envp)
{
	close(fd[0]);
	*fd_infile = open(argv[1], O_RDONLY);
	if (*fd_infile < 0)
		error_exit("Error\ninfile could not be opened", 1);
	if (dup2(*fd_infile, STDIN_FILENO) < 0)
		error_exit("Error\ndup2 failed in child_cmd1\n", 1);
	if(dup2(fd[1], STDOUT_FILENO) < 0)
		error_exit("Error\ndup2 failed in child_cmd1\n", 1);
	close(*fd_infile);
	close(fd[1]);
	do_execve_stuff(argv[2], envp);
	error_exit("Error\ncmd1 failed\n", 1);
}

/* child process 2 - cmd2
close writing end of pipe
0. open outfile
1. redirect standard input of cmd2 to the read end of the pipe
2. redirect standard output to the fd of file2
3. execute cmd2 (execve)
4. close outfile
X. close fds that are not used and pipe ends */
void	child_cmd_2(int *fd, int *fd_outfile, char **argv, char **envp)
{
	close(fd[1]);
	*fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_outfile < 0)
		error_exit("Error\noutfile could not be opened", 1);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		error_exit("Error\ndup2 failed in child_cmd2\n", 1);
	if (dup2(*fd_outfile, STDOUT_FILENO) < 0)
		error_exit("Error\ndup2 failed in child_cmd2\n", 1);
	close(*fd_outfile);
	close(fd[0]);
	do_execve_stuff(argv[3], envp);
	error_exit("Error\ncmd2 failed\n", 1);
}

void	error_exit(char *error_msg, int status)
{
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	exit(status);
}
