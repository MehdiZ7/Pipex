/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:42:21 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 18:07:31 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_cmd(char *cmd)
{
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	if (s_cmd == NULL)
	{
		ft_putstr_fd("Malloc error\n", 2);
		exit(1);
	}
	if (s_cmd[0] == NULL)
	{
		free_split(s_cmd);
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	return (s_cmd);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*find_path(char *cmd, char **env)
{
	char	*cmd_path;
	char	*env_path;
	char	**path;
	int		i;

	i = 0;
	env_path = get_env(env);
	if (!env_path)
		return (NULL);
	path = ft_split(env_path, ':');
	while (path[i])
	{
		cmd_path = build_cmd_path(cmd, path[i]);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (free_split(path), cmd_path);
		free(cmd_path);
		i++;
	}
	free_split(path);
	return (NULL);
}

char	*get_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*build_cmd_path(char *cmd, char *path)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cmd_path);
}
