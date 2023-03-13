/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:17:12 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/13 14:02:35 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char *name, char *message, int status)
{
	if (name)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
		ft_putchar_fd('\n', 2);
	}
	else
		perror(message);
	if (status != -1)
		exit(status);
}

int	set_return_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (0);
}
