/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:47:24 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/16 15:32:03 by rlouvrie         ###   ########.fr       */
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
	if (pipex.outfile < 0)
		exit (1);
	pipex.infile = open(argv[1], O_RDONLY, 0777);
	if (pipex.infile == -1)
		init_error(argv[1], strerror(errno), pipex, 1);
	if (pipe(pipex.fd) == -1)
		init_error(NULL, strerror(errno), pipex, 2);
	pipex.path = find_path(envp);
	if (!pipex.path)
		init_error(NULL, strerror(errno), pipex, 3);
	return (pipex);
}
