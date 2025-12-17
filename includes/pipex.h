/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:40:19 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 13:54:24 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

// Parsing

char	*get_env(char **env);
char	*find_path(char *cmd, char **env);
void	free_split(char **tab);
char	*build_cmd_path(char *cmd, char *path);
char	**get_cmd(char *cmd);

//pipex utils
int		process1(char **av, char **env, int *fd);
int		process2(char **av, char **env, int *fd);

#endif
