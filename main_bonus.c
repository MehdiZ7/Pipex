/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:37:04 by mzouhir           #+#    #+#             */
/*   Updated: 2025/12/09 18:27:07 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	multiple_pipe(int ac, char **av, char **env)
{
	int		status;
	pid_t	pid;

	open_infile(av[1]);
	loop_pipe(ac, av, env);
	pid = fork();
	if (pid == 0)
	{
		open_outfile(av[ac - 1]);
		execute(av[ac - 2], env);
	}
	close(0);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	heredoc_pipe(int ac, char **av, char **env)
{
	int		status;
	pid_t	pid;

	here_doc_input(av[2]);
	loop_pipe_heredoc(ac, av, env);
		pid = fork();
	if (pid == 0)
	{
		open_outfile_heredoc(av[ac - 1]);
		execute(av[ac - 2], env);
	}
	close(0);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
		return (ft_putstr_fd("Invalid arguments", 2), 1);
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		if (ac < 6)
			return (ft_putstr_fd("Invalid arguments here_doc", 2), 1);
		return (heredoc_pipe(ac, av, env));
	}
	else
		return (multiple_pipe(ac, av, env));
}
