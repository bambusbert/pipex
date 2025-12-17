/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:17 by slambert          #+#    #+#             */
/*   Updated: 2025/12/17 21:58:38 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* argv[1] = file1
argv[2] = cmd1
argv[3] = cmd2
argv[4] = file2 */
// TODO create one singular child process
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	if (argc < 5)
		custom_error("wrong input. Correct Input: ./pipex <file1> <cmd1> <cmd2> ... <cmd_n> <file2>",
			EXIT_FAILURE);
	init_struct(&pipex, argc, argv, envp);
	init_pipes(pipex);
	pipex.pid[0] = fork();
	if (pipex.pid[0] < 0)
		clean_exit("first fork failed", pipex.pipes[0], -1);
	if (pipex.pid[0] == 0)
		child(&pipex, 1);
	i = 1;
	while (i < pipex.cmd_count - 1)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] < 0)
			clean_exit("middle fork failed", pipex.pipes[i], -1);
		if (pipex.pid[i] == 0)
			child(&pipex, i + 1);
		i++;
	}
	pipex.pid[pipex.cmd_count - 1] = fork();
	if (pipex.pid[pipex.cmd_count - 1] < 0)
		clean_exit("second fork failed", pipex.pipes[0], -1);
	if (pipex.pid[pipex.cmd_count - 1] == 0)
		child(&pipex, i + 1);
	close_all_pipes(&pipex);
	return (return_handler(pipex.pid[0], pipex.pid[pipex.cmd_count - 1]));
}

void	init_pipes(t_pipex *pipex)
{
	int i;

	i = 0;
	
	while (i < pipex.cmd_count - 1)
	{
		if (pipe(pipex.pipes[i]) == -1)
			custom_error("pipe returned -1", EXIT_FAILURE);
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

void	child(t_pipex *pipex, int cmd_count)
{
	if (cmd_count == 1)
		child_cmd_first(pipex);
	else if (cmd_count == pipex->cmd_count)
		child_cmd_last(pipex);
	else
	{
		child_cmd_middle(pipex, cmd_count);
	}
}

// TODO error handling
void	init_struct(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;

	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd_count = argc - 3;
	// dprintf(2, "count cmds: %d\n", pipex->cmd_count);
	pipex->pid = malloc(sizeof(int) * (pipex->cmd_count));
	if (!pipex->pid)
	{
		// error handling
	}
	// dprintf(2, "count pipes: %d\n", pipex->cmd_count - 1);
	pipex->pipes = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (!pipex->pipes)
	{
		// error handling
	}
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
		{
			// error handling
		}
		i++;
	}
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

/* child process 1, cmd1
-1. close reading end of pipe
0. open infile
1. redirect standard input to fd pointing to file1
2. redirect output of cmd1 into the write end of the pipe
to test if that stuff works just comment out this line (output goes into stdout)
3. execute cmd1 (execve)
4. close infile
X. close fds that are not used and pipe ends */
void	child_cmd_first(t_pipex *pipex)
{
	pipex->fd_infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd_infile < 0)
		clean_exit("infile error", pipex->pipes[0], -1);
	if (dup2(pipex->fd_infile, STDIN_FILENO) < 0)
		clean_exit("dup2 infile error", pipex->pipes[0], pipex->fd_infile);
	if (dup2(pipex->pipes[0][1], STDOUT_FILENO) < 0)
		clean_exit("dup2 pipe error", pipex->pipes[0], pipex->fd_infile);
	close(pipex->fd_infile);
	close_all_pipes(pipex);
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
void	child_cmd_last(t_pipex *pipex)
{
	pipex->fd_outfile = open(pipex->argv[pipex->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_outfile < 0)
		clean_exit("outfile error", pipex->pipes[pipex->cmd_count - 2], -1);
	if (dup2(pipex->pipes[pipex->cmd_count - 2][0], STDIN_FILENO) < 0)
		clean_exit("dup2 pipe error", pipex->pipes[pipex->cmd_count - 2],
			pipex->fd_outfile);
	if (dup2(pipex->fd_outfile, STDOUT_FILENO) < 0)
		clean_exit("dup2 outfile error", pipex->pipes[pipex->cmd_count - 2],
			pipex->fd_outfile);
	close(pipex->fd_outfile);
	close_all_pipes(pipex);
	do_execve_stuff(pipex->argv[pipex->argc - 2], pipex->envp);
}

void	child_cmd_middle(t_pipex *pipex, int cmd_count)
{
	int	in_pipe;
	int	out_pipe;
	int	i;

	in_pipe = cmd_count - 2;
	out_pipe = cmd_count - 1;
	if (dup2(pipex->pipes[in_pipe][0], STDIN_FILENO) < 0)
		clean_exit("dup2 pipe error", pipex->pipes[in_pipe], -1);
	if (dup2(pipex->pipes[out_pipe][1], STDOUT_FILENO) < 0)
		clean_exit("dup2 outfile error", pipex->pipes[out_pipe], -1);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	do_execve_stuff(pipex->argv[cmd_count + 1], pipex->envp);
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

void	custom_error(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(status);
}