/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:47:24 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/10 17:40:53 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (1);
	if (pipe(pipex.fd) == -1)
		return (1);
	pipex.infile = open(argv[1], O_RDONLY, 0777);
	if (pipex.infile == -1)
		error_msg(argv[1], "no such file or directory: ", 2);
	pipex.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex.outfile < 0)
		return (1);
	pipex.path = find_path(envp);
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
