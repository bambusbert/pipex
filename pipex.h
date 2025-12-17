/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:42 by slambert          #+#    #+#             */
/*   Updated: 2025/12/17 14:40:41 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <errno.h>
#include <stdio.h> //TODO remove
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	do_execve_stuff(char *str, char **envp);
char	*extract_pathvar_from_envp(char **envp);
char	*extract_path_from_pathvar(char *path_var, char **strs);
void	free_2d(char **strs);
void	error_exit(char *error_msg, int status);
char	*check_single_path(char *path, char **paths, char *cmd);
void	child_cmd_1(int *fd, char **argv, char **envp);
void	child_cmd_2(int *fd, char **argv, char **envp);
int		is_empty(char *str);
char	*absolute_path_helper(char **strs);
void    clean_exit(char *msg, int *p_fd, int file_fd);
