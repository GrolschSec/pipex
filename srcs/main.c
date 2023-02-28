/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:47:24 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/02/28 14:27:57 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv)
{
	if (argc != 5)
		return (1);
	// argv[0] = Name.
	// argv[1] = Infile.
	// argv[2] = Cmd1 (to send infile in stdin).
	// argv[3] = Cmd2 (to send stdout of cmd1 in stdin).
	// argv[4] = Outfile (Save the stdout of cmd2 in it).
	// Example:
	//			./pipex tests/infile "grep a1" "wc -w" tests/outfile
	//
	// The above example must give the answer 5 saved in the outfile.
	ft_putstr_fd(argv[4], 0);
	return (0);
}