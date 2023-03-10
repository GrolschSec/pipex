/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:47:44 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/10 14:36:21 by rlouvrie         ###   ########.fr       */
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

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		infile;
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
/*process.c*/
void	free_child(t_pipex pipex);
void	close_pipes(t_pipex pipex);
void	parent_process(t_pipex pipex);
void	child_two_process(t_pipex pipex, char **argv, char **envp);
void	child_one_process(t_pipex pipex, char **argv, char **envp);
/*error.c*/
void	error_msg(char *name, char *message, int status);
int		set_return_value(int status);
#endif