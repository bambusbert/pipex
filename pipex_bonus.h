/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:42 by slambert          #+#    #+#             */
/*   Updated: 2025/12/17 20:17:03 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
    int argc;
    int fd_infile;
    int fd_outfile;
    int cmd_count;
    int pid1;   //will be replaced by *pid (points to an array with size cmd_count)
    int pid2;   //will be replaced by *pid (points to an array with size cmd_count)
    int fd[2];  //wll be replaced by **pipes (size: [cmd_count - 1][2]

    char **argv;
    char **envp;
}   t_pipex;

void    init_struct (t_pipex *pipex, int argc, char **argv, char **envp);
void	do_execve_stuff(char *str, char **envp);
char	*extract_pathvar_from_envp(char **envp);
char	*extract_path_from_pathvar(char *path_var, char **strs);
void	free_2d(char **strs);
void	error_exit(char *error_msg, int status);
char	*check_single_path(char *path, char **paths, char *cmd);
void	child_cmd_1(t_pipex *pipex);
void	child_cmd_2(t_pipex *pipex);
int		is_empty(char *str);
char	*absolute_path_helper(char **strs);
void	clean_exit(char *msg, int *p_fd, int file_fd);
int		return_handler(int pid1, int pid2);
void	custom_error(char *msg, int status);

#endif