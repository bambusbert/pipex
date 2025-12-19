/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:17 by slambert          #+#    #+#             */
/*   Updated: 2025/12/19 14:01:51 by slambert         ###   ########.fr       */
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
	int		ret;

	if (argc < 5)
		custom_error("wrong input. Correct Input: ./pipex <file1> <cmd1> <cmd2>\
			 ... <cmd_n> <file2>", EXIT_FAILURE);
	init_struct(&pipex, argc, argv, envp);
	init_pipes(&pipex);
	i = 0;
	while (i < pipex.cmd_count)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] < 0)
			clean_exit("fork failed", pipex.pipes[i], -1, &pipex);
		if (pipex.pid[i] == 0)
			child(&pipex, i + 1);
		i++;
	}
	close_all_pipes(&pipex);
	ret = return_handler(pipex.pid[0], pipex.pid[pipex.cmd_count - 1]);
	free_stuff(&pipex);
	return (ret);
}

void	child(t_pipex *pipex, int cmd_count)
{
	if (cmd_count == 1)
		child_cmd_first(pipex);
	else if (cmd_count == pipex->cmd_count)
		child_cmd_last(pipex);
	else
		child_cmd_middle(pipex, cmd_count);
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
		clean_exit("infile error", pipex->pipes[0], -1, pipex);
	if (dup2(pipex->fd_infile, STDIN_FILENO) < 0)
		clean_exit("dup2 infile error", pipex->pipes[0], pipex->fd_infile,
			pipex);
	if (dup2(pipex->pipes[0][1], STDOUT_FILENO) < 0)
		clean_exit("dup2 pipe error", pipex->pipes[0], pipex->fd_infile, pipex);
	close(pipex->fd_infile);
	close_all_pipes(pipex);
	do_execve_stuff(pipex->argv[2], pipex->envp, pipex);
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
		clean_exit("outfile error", pipex->pipes[pipex->cmd_count - 2], -1,
			pipex);
	if (dup2(pipex->pipes[pipex->cmd_count - 2][0], STDIN_FILENO) < 0)
		clean_exit("dup2 pipe error", pipex->pipes[pipex->cmd_count - 2],
			pipex->fd_outfile, pipex);
	if (dup2(pipex->fd_outfile, STDOUT_FILENO) < 0)
		clean_exit("dup2 outfile error", pipex->pipes[pipex->cmd_count - 2],
			pipex->fd_outfile, pipex);
	close(pipex->fd_outfile);
	close_all_pipes(pipex);
	do_execve_stuff(pipex->argv[pipex->argc - 2], pipex->envp, pipex);
}

void	child_cmd_middle(t_pipex *pipex, int cmd_count)
{
	int	in_pipe;
	int	out_pipe;
	int	i;

	in_pipe = cmd_count - 2;
	out_pipe = cmd_count - 1;
	if (dup2(pipex->pipes[in_pipe][0], STDIN_FILENO) < 0)
		clean_exit("dup2 pipe error", pipex->pipes[in_pipe], -1, pipex);
	if (dup2(pipex->pipes[out_pipe][1], STDOUT_FILENO) < 0)
		clean_exit("dup2 outfile error", pipex->pipes[out_pipe], -1, pipex);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	do_execve_stuff(pipex->argv[cmd_count + 1], pipex->envp, pipex);
}
