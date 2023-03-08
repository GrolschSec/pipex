/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:13:42 by romain            #+#    #+#             */
/*   Updated: 2023/03/08 23:16:11 by romain           ###   ########.fr       */
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

char *find_path(char **envp)
{
    char	*path;
	int		i;

	i = 0;
	path = NULL;
    while (envp[i] != NULL)
	{
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
            path = envp[i] + 5;
            break;
        }
		i++;
    }
    return path;
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

char	*find_app(char **envp, char *app_name)
{
    char	*path;
	char	*app_path;
	char	**dirs;
	int		i;
	
	path = find_path(envp);
    if (path == NULL)
        return NULL;
    dirs = ft_split(path, ':');
    if (!dirs)
		return (NULL);
	i = 0;
	app_path = NULL;
    while (dirs[i])
	{
		app_path = set_app_path(dirs[i++], app_name);
        if (access(app_path, X_OK) == 0)
			break;
		else
		{
			free(app_path);
			app_path = NULL;
		}
	}
	return (free_tab(dirs), app_path);
}
