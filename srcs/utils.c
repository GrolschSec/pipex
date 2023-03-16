/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:13:42 by romain            #+#    #+#             */
/*   Updated: 2023/03/16 11:16:34 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**find_path(char **envp)
{
	char	*path;
	char	**path_splitted;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (path)
	{
		path_splitted = ft_split(path, ':');
		if (!path_splitted)
			return (NULL);
	}	
	return (path_splitted);
}

char	*set_app_path(char *dir, char *name)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(dir, "/");
	if (!str1)
		return (NULL);
	str2 = ft_strjoin(str1, name);
	if (!str2)
		return (free(str1), NULL);
	return (free(str1), str2);
}

char	*find_app(t_pipex pipex, char *app_name)
{
	char	*app_path;
	int		i;

	i = 0;
	app_path = NULL;
	if (access(app_name, X_OK) == 0)
		return (name_is_path(pipex, app_name));
	while (pipex.path[i])
	{
		app_path = set_app_path(pipex.path[i++], app_name);
		if (access(app_path, X_OK) == 0)
			break ;
		else
		{
			free(app_path);
			app_path = NULL;
		}
	}
	return (app_path);
}

int	get_tab_size(char **tab)
{
	int	count;

	count = 0;
	while (tab[count])
		count++;
	return (count);
}
