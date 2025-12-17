/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:48:19 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 13:43:46 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = get_cmd(cmd);
	path = find_path(s_cmd[0], env);
	if (path == NULL)
	{
		free_split(s_cmd);
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		free_split(s_cmd);
		free(path);
		perror("execve");
		exit(1);
	}
}

int	process1(char **av, char **env, int *fd)
{
	int	fdfile;

	fdfile = open(av[1], O_RDONLY);
	if (fdfile == -1)
	{
		perror(av[1]);
		fdfile = open("/dev/null", O_RDONLY);
		if (fdfile == -1)
			exit(1);
	}
	dup2(fdfile, 0);
	dup2(fd[1], 1);
	close(fdfile);
	close(fd[0]);
	execute(av[2], env);
	return (0);
}

int	process2(char **av, char **env, int *fd)
{
	int	fdfile;

	fdfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdfile == -1)
	{
		perror(av[4]);
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(fdfile, 1);
	close(fdfile);
	close(fd[1]);
	execute(av[3], env);
	return (0);
}
