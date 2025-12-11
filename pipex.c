/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:17 by slambert          #+#    #+#             */
/*   Updated: 2025/12/11 19:22:02 by slambert         ###   ########.fr       */
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
	int fd[2];
	int pid1;
	int pid2;
	int fd_infile;

    if (argc != 5)
		return 1;
	if (pipe(fd) == -1)
		return (1);

	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		// child process 1, cmd1
        // 0. open infile
		fd_infile = open(argv[1], O_RDONLY);
		if (fd_infile < 0)
			return 1;
		printf("fd of infile: %d\n", fd_infile);
		// 1. redirect standard input to fd pointing to file1
		dup2(fd_infile, STDIN_FILENO);
		// 2. redirect output of cmd1 into the write end of the pipe
		dup2(fd[1], STDOUT_FILENO);
		// 3. execute cmd1 (execve)
		do_execve_stuff(argv[2], envp);
        // 4. close infile
		// X. close fds that are not used and pipe ends
	}
	

	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		// child process 2 - cmd2
        // 0. open outfile
		// 1. redirect standard input of cmd2 to the read end of the pipe
        // 2. redirect standard output to the fd of file2
		// 3. execute cmd2 (execve)
        // 4. close outfile
		// X. close fds that are not used and pipe ends
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}
