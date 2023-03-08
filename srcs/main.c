/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:47:24 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/09 00:21:26 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int *fd, char **envp, char **argv)
{
	int		infile;

	close(fd[0]);
	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		return ;	// error func should handle that error code 3 cannot handle file
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(infile);
	ft_exec(argv[2], envp);
}

void	parent_process(int *fd, char **envp, char **argv)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (outfile == -1)
		return ;	// error handle file opening error
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(outfile);
	ft_exec(argv[3], envp);
}

void	ft_exec(char *args, char **envp)
{
	char	**splitted;
	char	*path;
	
	splitted = ft_split(args, ' ');
	if (!splitted)
		return ;	// error handle memory allocation
	path = find_app(envp, splitted[0]);
	if (!path)
		return (free_tab(splitted)); // handle path not found
	execve(path, splitted, envp);
}

int	main(int argc, char **argv, char **envp)
{	
	// argv[0] = Name.
	// argv[1] = Infile (We have to read it).
	// argv[2] = Cmd1 (to send infile in stdin).
	// argv[3] = Cmd2 (to send stdout of cmd1 in stdin).
	// argv[4] = Outfile (Save the stdout of cmd2 in it).
	// Example:
	//			./pipex tests/infile "grep a1" "wc -w" tests/outfile
	// The above example must give the answer 5 saved in the outfile.
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (1); // function error() return 1 pipe error
		pid = fork();
		if (pid == -1)
			return (2); //function error() return 2 fork error
		if (pid == 0)
		{
			child_process(fd, envp, argv);
		}
		waitpid(pid, NULL, 0);
		parent_process(fd, envp, argv);
	}
	return (0);
}