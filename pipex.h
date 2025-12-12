/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:51:42 by slambert          #+#    #+#             */
/*   Updated: 2025/12/12 15:50:17 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>

void do_execve_stuff(char *str, char** envp);
char *extract_path_from_envp(char **envp);
char *extract_path_from_pathvar(char *path_var, char* cmd);
void free_2d (char **strs);
void error_exit (char *error_msg, int status);
char *check_single_path (char *path, char **paths, char *cmd);