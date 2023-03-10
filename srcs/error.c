/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:17:12 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/10 15:54:58 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char *name, char *message, int status)
{
	char	*str;

	if (name)
	{
		str = ft_strjoin(message, name);
		if (!str)
			return ;
		ft_putstr_fd(str, 2);
		free(str);
	}
	else
		perror(message);
	if (status != 0)
		exit(status);
}

int	set_return_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (0);
}
