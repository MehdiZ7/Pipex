/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:35:09 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 18:27:08 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_input(char *limiter)
{
	int		fd[2];
	char	*line;
	int		len;

	len = ft_strlen(limiter);
	pipe(fd);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			free(line);
			get_next_line(-1);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	loop_pipe_heredoc(int ac, char **av, char **env)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = 3;
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

void	open_outfile_heredoc(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}
