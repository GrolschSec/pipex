/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:17:12 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/23 03:51:11 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char *name, char *message, int status)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(message, 2);
	if (name)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(name, 2);
	}
	ft_putchar_fd('\n', 2);
	if (status != -1)
		exit(status);
}

void	init_error(char *name, char *message, t_pipex pipex, int err)
{
	if (err >= 1)
		close(pipex.outfile);
	if (err >= 2)
		close(pipex.infile);
	if (err >= 3)
	{
		close(pipex.fd[0]);
		close(pipex.fd[1]);
	}
	if (err >= 4)
	{
		close(pipex.error_fd[0]);
		close(pipex.error_fd[1]);
	}
	error_msg(name, message, 0);
}

int	set_return_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (0);
}

void	err_p1_app(t_pipex pipex, int choice)
{
	unsigned char	sync_byte;

	if (choice == 1)
	{
		sync_byte = 0;
		write(pipex.error_fd[1], &sync_byte, 1);
		error_msg(pipex.args[0], "command not found", -1);
		sync_byte = 1;
		write(pipex.error_fd[1], &sync_byte, 1);
		free_child(pipex);
		close(pipex.error_fd[1]);
		exit(127);
	}
	else if (choice == 0)
	{
		sync_byte = 1;
		write(pipex.error_fd[1], &sync_byte, 1);
		close(pipex.error_fd[1]);
	}
}

void	err_p2_app(t_pipex pipex)
{
	unsigned char	sync_byte;

	while (1)
	{
		read(pipex.error_fd[0], &sync_byte, 1);
		if (sync_byte == 1)
			break ;
	}
	close(pipex.error_fd[0]);
	error_msg(pipex.args[0], "command not found", -1);
	free_child(pipex);
	exit(127);
}
