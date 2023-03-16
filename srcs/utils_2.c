/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:16:12 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/16 11:16:36 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*name_is_path(t_pipex pipex, char *name)
{
	char	*app_path;
	char	**path_splitted;
	int		tab_size;
	int		name_len;

	app_path = malloc(sizeof(char) * (ft_strlen(name) + 1));
	if (!app_path)
		return (NULL);
	path_splitted = ft_split(name, '/');
	if (!path_splitted)
		return (free(app_path), NULL);
	tab_size = get_tab_size(path_splitted);
	name_len = ft_strlen(path_splitted[tab_size - 1]) + 1;
	pipex.args[0] = malloc(sizeof(char) * name_len);
	if (!pipex.args[0])
	{
		free(app_path);
		free_tab(path_splitted);
		return (NULL);
	}
	ft_strlcpy(pipex.args[0], path_splitted[tab_size - 1], name_len);
	ft_strlcpy(app_path, name, ft_strlen(name) + 1);
	return (app_path);
}
