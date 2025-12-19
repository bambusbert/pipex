/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:42 by slambert          #+#    #+#             */
/*   Updated: 2025/12/19 14:24:33 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		argc;
	int		fd_infile;
	int		fd_outfile;
	int		pid1;
	int		pid2;
	int		fd[2];
	char	**argv;
	char	**envp;
}			t_pipex;

void		init_struct(t_pipex *pipex, int argc, char **argv, char **envp);
void		do_execve_stuff(char *str, char **envp);
char		*extract_pathvar_from_envp(char **envp);
char		*extract_path_from_pathvar(char *path_var, char **strs);
void		free_2d(char **strs);
void		error_exit(char *error_msg, int status);
char		*check_single_path(char *path, char **paths, char *cmd);
void		child_cmd_1(t_pipex *pipex);
void		child_cmd_2(t_pipex *pipex);
char		*absolute_path_helper(char **strs);
void		clean_exit(char *msg, int *p_fd, int file_fd);
int			return_handler(int pid1, int pid2);
void		custom_error(char *msg, int status);
void		free2d_and_error_exit(char **arr, char *error_msg, int status);

#endif