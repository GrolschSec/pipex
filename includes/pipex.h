/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:47:44 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/03/09 00:06:50 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../ft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

// utils.c
void	free_tab(char **tab);
char	*find_path(char **envp);
char	*set_app_path(char *dir, char *name);
char	*find_app(char **envp, char *app_name);
// main.c
void	ft_exec(char *args, char **envp);
#endif