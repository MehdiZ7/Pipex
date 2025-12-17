/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:28:40 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 15:18:43 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
			exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void	open_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

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

void	child_process(char *cmd, char **env, int *fd)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	execute(cmd, env);
}

void	loop_pipe(int ac, char **av, char **env)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = 2;
	while (i < ac - 2)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child_process(av[i], env, fd);
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		i++;
	}
}
