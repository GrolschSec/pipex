/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:12:25 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/13 14:52:58 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_one_process(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd[1], STDOUT_FILENO);
	close(pipex.fd[0]);
	dup2(pipex.infile, STDIN_FILENO);
	close_pipes(pipex);
	pipex.args = ft_split(argv[2], ' ');
	pipex.app = find_app(pipex, pipex.args[0]);
	if (!pipex.app)
	{
		error_msg(pipex.args[0], "command not found", -1);
		free_child(pipex);
		exit(127);
	}
	if (execve(pipex.app, pipex.args, envp) == -1)
	{
		free_child(pipex);
		exit(0);
	}
}

void	child_two_process(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd[0], STDIN_FILENO);
	close(pipex.fd[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.args = ft_split(argv[3], ' ');
	pipex.app = find_app(pipex, pipex.args[0]);
	if (!pipex.app)
	{
		error_msg(pipex.args[0], "command not found", -1);
		free_child(pipex);
		exit(127);
	}
	if (execve(pipex.app, pipex.args, envp) == -1)
	{
		free_child(pipex);
		exit(0);
	}
}

void	parent_process(t_pipex pipex)
{
	close(pipex.infile);
	close(pipex.outfile);
	free_tab(pipex.path);
}

void	close_pipes(t_pipex pipex)
{
	close(pipex.fd[0]);
	close(pipex.fd[1]);
}

void	free_child(t_pipex pipex)
{
	free(pipex.app);
	free_tab(pipex.args);
	free_tab(pipex.path);
}
