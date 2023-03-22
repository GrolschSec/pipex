/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:47:44 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/22 23:42:11 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../ft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		error_fd[2];
	int		infile;
	int		in_exist;
	int		outfile;
	char	**path;
	char	**args;
	char	*app;
	int		status;
}				t_pipex;
/*utils.c*/
void	free_tab(char **tab);
char	**find_path(char **envp);
char	*set_app_path(char *dir, char *name);
char	*find_app(t_pipex pipex, char *app_name);
int		get_tab_size(char **tab);
/*utils_2.c*/
char	*name_is_path(t_pipex pipex, char *name);
/*process.c*/
void	free_child(t_pipex pipex);
void	close_pipes(t_pipex pipex);
void	parent_process(t_pipex pipex);
void	child_two_process(t_pipex pipex, char **argv, char **envp);
void	child_one_process(t_pipex pipex, char **argv, char **envp);
/*error.c*/
void	error_msg(char *name, char *message, int status);
void	init_error(char *name, char *message, t_pipex pipex, int err);
int		set_return_value(int status);
void	err_p1_app(t_pipex pipex, int choice);
void	err_p2_app(t_pipex pipex);
/*main.c*/
t_pipex	init(char **argv, char **envp);
#endif