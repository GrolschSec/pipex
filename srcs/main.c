/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:47:24 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/22 22:51:51 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		error_msg(NULL, "Not enough arguments", 1);
	pipex = init(argv, envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_one_process(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_two_process(pipex, argv, envp);
	close_pipes(pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &pipex.status, 0);
	parent_process(pipex);
	return (set_return_value(pipex.status));
}

t_pipex	init(char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (pipex.outfile == -1)
		exit (1);
	pipex.infile = open(argv[1], O_RDONLY, 0777);
	if (pipex.infile == -1)
	{
		error_msg(argv[1], strerror(errno), -1);
		pipex.in_exist = -1;
		pipex.infile = open("/dev/null", O_RDWR, 0777);
		if (pipex.infile == -1)
			init_error(NULL, strerror(errno), pipex, 1);
	}
	else
		pipex.in_exist = 0;
	if (pipe(pipex.fd) == -1)
		init_error(NULL, strerror(errno), pipex, 2);
	if (pipe(pipex.error_fd) == -1)
		init_error(NULL, strerror(errno), pipex, 3);
	pipex.path = find_path(envp);
	if (!pipex.path)
		init_error(NULL, strerror(errno), pipex, 4);
	return (pipex);
}
